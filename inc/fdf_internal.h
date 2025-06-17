#ifndef FDF_INTERNAL_H
# define FDF_INTERNAL_H

/* ************************************************************************** */
/*                          INTERNAL CONSTANTS & ENUMS                       */
/* ************************************************************************** */
// Mathematical constants
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

// Key codes (fixed system values)
typedef enum e_key_codes {
	KEY_ESC = 65307,
	KEY_W = 119,
	KEY_A = 97,
	KEY_S = 115,
	KEY_D = 100,
	KEY_Q = 113,
	KEY_E = 101,
	KEY_R = 114,
	KEY_T = 116,
	KEY_UP = 65362,
	KEY_DOWN = 65364,
	KEY_LEFT = 65361,
	KEY_RIGHT = 65363,
	KEY_PLUS = 61,
	KEY_MINUS = 45,
	KEY_SPACE = 32,
	KEY_TAB = 65289,
	KEY_ALT_L = 65513,
	KEY_ALT_R = 65514,
	KEY_Z = 122,
	KEY_X = 120
} t_key_codes;

// Mouse button codes
typedef enum e_mouse_buttons {
	MOUSE_LEFT_BUTTON = 1,
	MOUSE_RIGHT_BUTTON = 3,
	MOUSE_SCROLL_UP = 4,
	MOUSE_SCROLL_DOWN = 5
} t_mouse_buttons;

// Shape types
typedef enum e_shape_type {
	SHAPE_TYPE_FLAT = 0,
	SHAPE_TYPE_SPHERE = 1,
	SHAPE_TYPE_CYLINDER = 2,
	SHAPE_TYPE_CONE = 3,
	SHAPE_TYPE_WAVE = 4,
	SHAPE_TYPE_TORUS = 5,
	SHAPE_TYPE_SADDLE = 6,
	SHAPE_TYPE_HELIX = 7,
	SHAPE_TYPE_RIPPLE = 8,
	NUM_SHAPES = 9
} t_shape_type;

// Color themes
typedef enum e_color_theme {
	THEME_DEFAULT = 0,
	THEME_EARTH = 1,
	THEME_FIRE = 2,
	THEME_OCEAN = 3,
	THEME_RAINBOW = 4,
	THEME_MONO = 5,
	THEME_SUNSET = 6,
	THEME_ARCTIC = 7,
	THEME_NEON = 8,
	THEME_DESERT = 9,
	NUM_THEMES = 10
} t_color_theme;

/* ************************************************************************** */
/*                          THEME SKELETON STRUCTURE                         */
/* ************************************************************************** */

// Core theme colors that every theme must define
typedef struct s_theme_colors
{
	// Background and base colors
	int background;         // Main background color
	int ground;            // Ground/base level color
	int default_color;     // Default point color
	
	// Gradient points for height mapping (low to high)
	int depth_bottom;      // Lowest/deepest points
	int depth_low;         // Below-average depth
	int middle;            // Sea level / average height
	int elevation_mid;     // Above-average elevation
	int elevation_high;    // High peaks
	int elevation_top;     // Highest peaks
	
	// UI and accent colors
	int foreground;        // Text and UI elements
	int accent;            // Highlights and selection
	int secondary;         // Secondary UI elements
	
	// Special effect colors
	int special_1;         // Theme-specific color 1
	int special_2;         // Theme-specific color 2
} t_theme_colors;

// Theme metadata and configuration
typedef struct s_theme_config
{
	const char      *name;
	const char      *description;
	t_theme_colors  colors;
	int             gradient_steps;    // Number of interpolation steps
	int             use_smooth;        // Use smooth gradients vs hard transitions
	float           contrast;          // Contrast multiplier (0.5 - 2.0)
	float           brightness;        // Brightness adjustment (-1.0 to 1.0)
} t_theme_config;

// Function pointer for theme color calculation
typedef int (*theme_func_t)(int z_value, int min_z, int max_z, const t_theme_config *config);

// Theme registry entry
typedef struct s_theme_entry
{
	t_color_theme   id;
	t_theme_config  config;
	theme_func_t    calculator;
} t_theme_entry;

// Internal system constants (INTEGER ONLY)
typedef enum e_system_constants {
	ALT_MASK = 8,           // 0x08 in decimal
	RENORM_COUNT = 97,
	MAX_COLOR_INDEX = 255,
	FIT = 1,
	FREE = 0
} t_system_constants;

#endif