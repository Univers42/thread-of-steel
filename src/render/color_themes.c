/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_themes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:15:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/17 16:05:24 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* ************************************************************************** */
/*                          FORWARD DECLARATIONS                             */
/* ************************************************************************** */

static int	get_themed_color_uncached(int z_value, int min_z, int max_z, int theme);

/* ************************************************************************** */
/*                          COLOR CACHE STRUCTURE                            */
/* ************************************************************************** */

typedef struct s_color_cache
{
	int		last_z;
	int		last_min_z;
	int		last_max_z;
	int		last_theme;
	int		cached_color;
	int		valid;
} t_color_cache;

/* ************************************************************************** */
/*                          COLOR UTILITY FUNCTIONS                          */
/* ************************************************************************** */

static int	color_to_int(t_color color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}

static t_color	int_to_color(int color_int)
{
	t_color	color;

	color.r = (color_int >> 16) & 0xFF;
	color.g = (color_int >> 8) & 0xFF;
	color.b = color_int & 0xFF;
	color.alpha = 255;
	return (color);
}

static t_color	interpolate_colors(t_color c1, t_color c2, float t)
{
	t_color	result;

	if (t <= 0.0f)
		return (c1);
	if (t >= 1.0f)
		return (c2);
	result.r = (int)(c1.r + t * (c2.r - c1.r));
	result.g = (int)(c1.g + t * (c2.g - c1.g));
	result.b = (int)(c1.b + t * (c2.b - c1.b));
	result.alpha = (int)(c1.alpha + t * (c2.alpha - c1.alpha));
	return (result);
}

static t_color	denormalize_color(t_color_float normalized)
{
	t_color	result;

	result.r = (int)(normalized.r * 255.0f);
	result.g = (int)(normalized.g * 255.0f);
	result.b = (int)(normalized.b * 255.0f);
	result.alpha = (int)(normalized.alpha * 255.0f);
	result.r = (result.r < 0) ? 0 : (result.r > 255) ? 255 : result.r;
	result.g = (result.g < 0) ? 0 : (result.g > 255) ? 255 : result.g;
	result.b = (result.b < 0) ? 0 : (result.b > 255) ? 255 : result.b;
	result.alpha = (result.alpha < 0) ? 0 : (result.alpha > 255) ? 255 : result.alpha;
	return (result);
}

static t_color	apply_color_properties(t_color color, t_color_properties props)
{
	t_color_float	normalized;
	t_color_float	adjusted;

	normalized.r = (float)color.r / 255.0f;
	normalized.g = (float)color.g / 255.0f;
	normalized.b = (float)color.b / 255.0f;
	normalized.alpha = (float)color.alpha / 255.0f;
	adjusted.r = ((normalized.r - 0.5f) * props.contrast + 0.5f) + props.brightness;
	adjusted.g = ((normalized.g - 0.5f) * props.contrast + 0.5f) + props.brightness;
	adjusted.b = ((normalized.b - 0.5f) * props.contrast + 0.5f) + props.brightness;
	adjusted.r = powf(adjusted.r, 1.0f / props.gamma);
	adjusted.g = powf(adjusted.g, 1.0f / props.gamma);
	adjusted.b = powf(adjusted.b, 1.0f / props.gamma);
	if (props.invert)
	{
		adjusted.r = 1.0f - adjusted.r;
		adjusted.g = 1.0f - adjusted.g;
		adjusted.b = 1.0f - adjusted.b;
	}
	adjusted.alpha = normalized.alpha;
	return (denormalize_color(adjusted));
}

/* ************************************************************************** */
/*                          HSV COLOR CONVERSION                             */
/* ************************************************************************** */

static void	assign_rgb_values(int h_i, float c, float x, t_color_float *rgb)
{
	if (h_i == 0)
	{
		rgb->r = c;
		rgb->g = x;
		rgb->b = 0;
	}
	else if (h_i == 1)
	{
		rgb->r = x;
		rgb->g = c;
		rgb->b = 0;
	}
	else if (h_i == 2)
	{
		rgb->r = 0;
		rgb->g = c;
		rgb->b = x;
	}
	else if (h_i == 3)
	{
		rgb->r = 0;
		rgb->g = x;
		rgb->b = c;
	}
	else if (h_i == 4)
	{
		rgb->r = x;
		rgb->g = 0;
		rgb->b = c;
	}
	else
	{
		rgb->r = c;
		rgb->g = 0;
		rgb->b = x;
	}
}

static t_color	hsv_to_color(t_hue hsv)
{
	t_color			color;
	t_color_float	rgb;
	float			c;
	float			x;
	float			m;
	int				h_i;

	c = hsv.value * hsv.saturation;
	x = c * (1.0f - fabsf(fmodf(hsv.hue / 60.0f, 2.0f) - 1.0f));
	m = hsv.value - c;
	h_i = (int)(hsv.hue / 60.0f) % 6;
	assign_rgb_values(h_i, c, x, &rgb);
	color.r = (int)((rgb.r + m) * 255.0f);
	color.g = (int)((rgb.g + m) * 255.0f);
	color.b = (int)((rgb.b + m) * 255.0f);
	color.alpha = (int)(hsv.alpha * 255.0f);
	return (color);
}

/* ************************************************************************** */
/*                          GRADIENT CALCULATION                             */
/* ************************************************************************** */

static t_color	evaluate_gradient(t_gradient *gradient, float t)
{
	int		i;
	float	local_t;

	if (!gradient || gradient->num_stops == 0)
		return ((t_color){255, 255, 255, 255});
	if (gradient->num_stops == 1 || t <= gradient->stops[0].position)
		return (gradient->stops[0].color);
	if (t >= gradient->stops[gradient->num_stops - 1].position)
		return (gradient->stops[gradient->num_stops - 1].color);
	i = 0;
	while (i < gradient->num_stops - 1)
	{
		if (t >= gradient->stops[i].position && t <= gradient->stops[i + 1].position)
		{
			local_t = (t - gradient->stops[i].position) / 
				(gradient->stops[i + 1].position - gradient->stops[i].position);
			if (gradient->smooth)
				return (interpolate_colors(gradient->stops[i].color, 
					gradient->stops[i + 1].color, local_t));
			else
				return (gradient->stops[i].color);
		}
		i++;
	}
	return (gradient->stops[gradient->num_stops - 1].color);
}

/* ************************************************************************** */
/*                          MEMORY MANAGEMENT                                */
/* ************************************************************************** */

static void	free_gradient(t_gradient *gradient)
{
	if (gradient && gradient->stops)
	{
		free(gradient->stops);
		gradient->stops = NULL;
		gradient->num_stops = 0;
	}
}

static int	create_gradient(t_gradient *gradient, const int *colors, 
			int num_colors, const float *positions)
{
	int	i;

	gradient->stops = malloc(sizeof(t_gradient_stop) * num_colors);
	if (!gradient->stops)
		return (0);
	gradient->num_stops = num_colors;
	gradient->smooth = 1;
	i = 0;
	while (i < num_colors)
	{
		gradient->stops[i].position = positions[i];
		gradient->stops[i].color = int_to_color(colors[i]);
		i++;
	}
	return (1);
}

/* ************************************************************************** */
/*                          OPTIMIZED THEME INITIALIZATION                   */
/* ************************************************************************** */

static void	init_theme_gradient(t_gradient *gradient, t_color_theme theme_id)
{
	static const int	default_colors[] = {
		THEME_DEFAULT_DEPTH_BOTTOM, THEME_DEFAULT_DEPTH_LOW,
		THEME_DEFAULT_MIDDLE, THEME_DEFAULT_ELEVATION_MID,
		THEME_DEFAULT_ELEVATION_HIGH, THEME_DEFAULT_ELEVATION_TOP
	};
	static const int	earth_colors[] = {
		THEME_EARTH_DEPTH_BOTTOM, THEME_EARTH_DEPTH_LOW,
		THEME_EARTH_MIDDLE, THEME_EARTH_ELEVATION_MID,
		THEME_EARTH_ELEVATION_HIGH, THEME_EARTH_ELEVATION_TOP
	};
	static const float	positions[] = {0.0f, 0.2f, 0.4f, 0.6f, 0.8f, 1.0f};

	if (theme_id == THEME_DEFAULT)
		create_gradient(gradient, default_colors, 6, positions);
	else if (theme_id == THEME_EARTH)
		create_gradient(gradient, earth_colors, 6, positions);
}

static void	init_theme_properties(t_advanced_theme *theme, t_color_theme id)
{
	static const t_color_properties	theme_props[] = {
		{1.0f, 0.0f, 1.0f, 2.2f, 0.0f, 0},  // DEFAULT
		{1.2f, 0.1f, 1.1f, 2.2f, 0.0f, 0},  // EARTH
		{1.5f, 0.0f, 1.0f, 2.2f, 0.0f, 0},  // FIRE
		{1.1f, -0.1f, 1.0f, 2.2f, 0.0f, 0}, // OCEAN
		{1.3f, 0.0f, 1.5f, 2.2f, 0.0f, 0}   // RAINBOW
	};

	if (id < NUM_THEMES)
		theme->properties = theme_props[id];
}

static void	init_theme_colors(t_advanced_theme *theme, t_color_theme id)
{
	static const int	backgrounds[] = {
		THEME_DEFAULT_BACKGROUND, THEME_EARTH_BACKGROUND,
		THEME_FIRE_BACKGROUND, THEME_OCEAN_BACKGROUND, 0x000000
	};
	static const int	foregrounds[] = {
		THEME_DEFAULT_FOREGROUND, THEME_EARTH_FOREGROUND,
		THEME_FIRE_FOREGROUND, THEME_OCEAN_FOREGROUND, 0xFFFFFF
	};
	static const int	accents[] = {
		THEME_DEFAULT_ACCENT, THEME_EARTH_ACCENT,
		THEME_FIRE_ACCENT, THEME_OCEAN_ACCENT, 0xFF00FF
	};

	if (id < NUM_THEMES)
	{
		theme->background = int_to_color(backgrounds[id]);
		theme->foreground = int_to_color(foregrounds[id]);
		theme->accent = int_to_color(accents[id]);
	}
}

static void	init_single_theme(t_advanced_theme *theme, t_color_theme id)
{
	static const char	*names[] = {
		"Default", "Earth", "Fire", "Ocean", "Rainbow",
		"Mono", "Sunset", "Arctic", "Neon", "Desert"
	};
	static const char	*descriptions[] = {
		"Clean minimal theme", "Natural terrain colors",
		"Heat and energy theme", "Deep sea colors",
		"Full spectrum colors", "Monochrome grayscale",
		"Sunset colors", "Arctic ice colors",
		"Cyberpunk aesthetic", "Desert and mars colors"
	};

	if (id >= NUM_THEMES)
		return ;
	theme->name = names[id];
	theme->description = descriptions[id];
	theme->use_hue_shift = (id == THEME_RAINBOW) ? 1 : 0;
	theme->hue_shift_speed = (id == THEME_RAINBOW) ? 1.0f : 0.0f;
	init_theme_colors(theme, id);
	init_theme_properties(theme, id);
	init_theme_gradient(&theme->height_gradient, id);
}

/* ************************************************************************** */
/*                          OPTIMIZED REGISTRY                               */
/* ************************************************************************** */

static t_advanced_theme	*get_advanced_theme_registry(void)
{
	static t_advanced_theme	themes[NUM_THEMES];
	static int				initialized = 0;
	int						i;

	if (!initialized)
	{
		i = 0;
		while (i < NUM_THEMES)
		{
			init_single_theme(&themes[i], i);
			i++;
		}
		initialized = 1;
	}
	return (themes);
}

/* ************************************************************************** */
/*                          CLEANUP FUNCTIONS                                */
/* ************************************************************************** */

void	cleanup_theme_resources(void)
{
	t_advanced_theme	*themes;
	int					i;

	themes = get_advanced_theme_registry();
	i = 0;
	while (i < NUM_THEMES)
	{
		free_gradient(&themes[i].height_gradient);
		i++;
	}
}

/* ************************************************************************** */
/*                          OPTIMIZED COLOR CACHE                            */
/* ************************************************************************** */

static int	get_themed_color_uncached(int z_value, int min_z, int max_z, int theme)
{
	t_advanced_theme	*themes;
	float				t;
	t_color				result_color;
	t_hue				hsv;

	themes = get_advanced_theme_registry();
	if (theme < 0 || theme >= NUM_THEMES)
		theme = THEME_DEFAULT;
	if (max_z == min_z)
		return (color_to_int(themes[theme].background));
	t = (float)(z_value - min_z) / (float)(max_z - min_z);
	if (themes[theme].use_hue_shift)
	{
		hsv.hue = t * 360.0f;
		hsv.saturation = 1.0f;
		hsv.value = 1.0f;
		hsv.alpha = 1.0f;
		result_color = hsv_to_color(hsv);
	}
	else
		result_color = evaluate_gradient(&themes[theme].height_gradient, t);
	result_color = apply_color_properties(result_color, themes[theme].properties);
	return (color_to_int(result_color));
}

static int	get_cached_color(int z_value, int min_z, int max_z, int theme)
{
	static t_color_cache	cache = {0, 0, 0, 0, 0, 0};

	if (cache.valid && cache.last_z == z_value && 
		cache.last_min_z == min_z && cache.last_max_z == max_z && 
		cache.last_theme == theme)
		return (cache.cached_color);
	cache.last_z = z_value;
	cache.last_min_z = min_z;
	cache.last_max_z = max_z;
	cache.last_theme = theme;
	cache.cached_color = get_themed_color_uncached(z_value, min_z, max_z, theme);
	cache.valid = 1;
	return (cache.cached_color);
}

/* ************************************************************************** */
/*                          PUBLIC INTERFACE                                 */
/* ************************************************************************** */

int	get_themed_color(int z_value, int min_z, int max_z, int theme)
{
	if (theme < 0 || theme >= NUM_THEMES)
		theme = THEME_DEFAULT;
	return (get_cached_color(z_value, min_z, max_z, theme));
}

const char	*get_theme_name(int theme)
{
	t_advanced_theme	*themes;

	themes = get_advanced_theme_registry();
	if (theme < 0 || theme >= NUM_THEMES)
		return ("Unknown");
	return (themes[theme].name);
}

const char	*get_theme_description(int theme)
{
	t_advanced_theme	*themes;

	themes = get_advanced_theme_registry();
	if (theme < 0 || theme >= NUM_THEMES)
		return ("No description available");
	return (themes[theme].description);
}

int	get_theme_background(int theme)
{
	t_advanced_theme	*themes;

	themes = get_advanced_theme_registry();
	if (theme < 0 || theme >= NUM_THEMES)
		theme = THEME_DEFAULT;
	return (color_to_int(themes[theme].background));
}

int	get_theme_accent(int theme)
{
	t_advanced_theme	*themes;

	themes = get_advanced_theme_registry();
	if (theme < 0 || theme >= NUM_THEMES)
		theme = THEME_DEFAULT;
	return (color_to_int(themes[theme].accent));
}