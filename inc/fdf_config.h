#ifndef FDF_CONFIG_H
# define FDF_CONFIG_H

/* ************************************************************************** */
/*                          USER CONFIGURABLE SETTINGS                       */
/* ************************************************************************** */

// Window dimensions (user can modify for different screen sizes)
# define WIN_WIDTH                      1920
# define WIN_HEIGHT                     1080

// Default camera settings (user can tune for better initial view)
# define DEFAULT_ZOOM                   20
# define DEFAULT_Z_SCALE               1
# define DEFAULT_ANGLE_X               -0.5
# define DEFAULT_ANGLE_Y               0.0
# define DEFAULT_ANGLE_Z               0.5

// Mouse and keyboard sensitivity (user can adjust for preference)
# define MOUSE_ROTATION_SENSITIVITY     0.003
# define MOUSE_ZOOM_SENSITIVITY         1.1
# define MOUSE_FPS                      0.016   // ~60FPS
# define SNAP_ROTATION_SPEED            90.0f   //speed 
// Trackball settings (floating-point constants)
# define TRACKBALL_SIZE                 1.2f

// Performance settings (user can tune for hardware)
# define LARGE_MAP_THRESHOLD           10000
# define FIT_MARGIN                    50

# define LAT 0
# define LONG 1

// Visual settings (user can customize appearance)
# define DEFAULT_COLOR                 0xFFFFFF
# define BOTTOM_COLOR                  0x0000FF
# define TOP_COLOR                     0xFF0000
# define GROUND_COLOR                  0xDAA520
# define BACK_COLOR                    0x151515
# define MENU_COLOR                    0x202020
# define TEXT_COLOR                    0xEAEAEA
# define NUMBER_COLOR                  0xF3AF3D
# define MENU_WIDTH                    350

/********************************************************/
/* THEMES*/
/*******************************************************/

// Default Theme - Clean and minimal
# define THEME_DEFAULT_BACKGROUND      0x151515
# define THEME_DEFAULT_GROUND          0x333333
# define THEME_DEFAULT_DEFAULT         0xFFFFFF
# define THEME_DEFAULT_DEPTH_BOTTOM    0x000033
# define THEME_DEFAULT_DEPTH_LOW       0x003366
# define THEME_DEFAULT_MIDDLE          0x666666
# define THEME_DEFAULT_ELEVATION_MID   0x999999
# define THEME_DEFAULT_ELEVATION_HIGH  0xCCCCCC
# define THEME_DEFAULT_ELEVATION_TOP   0xFFFFFF
# define THEME_DEFAULT_FOREGROUND      0xEAEAEA
# define THEME_DEFAULT_ACCENT          0xF3AF3D
# define THEME_DEFAULT_SECONDARY       0x202020
# define THEME_DEFAULT_SPECIAL_1       0x4A90E2
# define THEME_DEFAULT_SPECIAL_2       0x7ED321

// Earth Theme - Natural terrain colors
# define THEME_EARTH_BACKGROUND        0x87CEEB
# define THEME_EARTH_GROUND            0x8B7355
# define THEME_EARTH_DEFAULT           0x90EE90
# define THEME_EARTH_DEPTH_BOTTOM      0x000080  // Deep ocean
# define THEME_EARTH_DEPTH_LOW         0x4169E1  // Shallow water
# define THEME_EARTH_MIDDLE            0x90EE90  // Sea level/grass
# define THEME_EARTH_ELEVATION_MID     0x228B22  // Forest
# define THEME_EARTH_ELEVATION_HIGH    0x8B4513  // Mountain
# define THEME_EARTH_ELEVATION_TOP     0xFFFFFF  // Snow caps
# define THEME_EARTH_FOREGROUND        0x2F4F4F
# define THEME_EARTH_ACCENT            0x32CD32
# define THEME_EARTH_SECONDARY         0x556B2F
# define THEME_EARTH_SPECIAL_1         0xFFA500  // Sunset
# define THEME_EARTH_SPECIAL_2         0x87CEEB  // Sky

// Fire Theme - Heat and energy
# define THEME_FIRE_BACKGROUND         0x000000
# define THEME_FIRE_GROUND             0x330000
# define THEME_FIRE_DEFAULT            0xFF4500
# define THEME_FIRE_DEPTH_BOTTOM       0x000000  // Cold/black
# define THEME_FIRE_DEPTH_LOW          0x8B0000  // Dark red
# define THEME_FIRE_MIDDLE             0xFF4500  // Orange red
# define THEME_FIRE_ELEVATION_MID      0xFF8C00  // Dark orange
# define THEME_FIRE_ELEVATION_HIGH     0xFFD700  // Gold
# define THEME_FIRE_ELEVATION_TOP      0xFFFFE0  // Light yellow
# define THEME_FIRE_FOREGROUND         0xFFE4E1
# define THEME_FIRE_ACCENT             0xFF6347
# define THEME_FIRE_SECONDARY          0x8B0000
# define THEME_FIRE_SPECIAL_1          0xFF1493  // Hot pink
# define THEME_FIRE_SPECIAL_2          0x00FF00  // Contrast green

// Ocean Theme - Deep sea colors
# define THEME_OCEAN_BACKGROUND        0x000033
# define THEME_OCEAN_GROUND            0x191970
# define THEME_OCEAN_DEFAULT           0x4682B4
# define THEME_OCEAN_DEPTH_BOTTOM      0x000033  // Abyss
# define THEME_OCEAN_DEPTH_LOW         0x191970  // Deep blue
# define THEME_OCEAN_MIDDLE            0x4682B4  // Steel blue
# define THEME_OCEAN_ELEVATION_MID     0x87CEEB  // Sky blue
# define THEME_OCEAN_ELEVATION_HIGH    0xB0E0E6  // Powder blue
# define THEME_OCEAN_ELEVATION_TOP     0xF0F8FF  // Alice blue
# define THEME_OCEAN_FOREGROUND        0xE0FFFF
# define THEME_OCEAN_ACCENT            0x00CED1
# define THEME_OCEAN_SECONDARY         0x2F4F4F
# define THEME_OCEAN_SPECIAL_1         0x7FFFD4  // Aquamarine
# define THEME_OCEAN_SPECIAL_2         0xFF6347  // Coral

// Neon Theme - Cyberpunk aesthetic
# define THEME_NEON_BACKGROUND         0x0A0A0A
# define THEME_NEON_GROUND             0x1A0033
# define THEME_NEON_DEFAULT            0xFF00FF
# define THEME_NEON_DEPTH_BOTTOM       0x000000  // Black
# define THEME_NEON_DEPTH_LOW          0x4B0082  // Indigo
# define THEME_NEON_MIDDLE             0xFF00FF  // Magenta
# define THEME_NEON_ELEVATION_MID      0x00FF00  // Lime
# define THEME_NEON_ELEVATION_HIGH     0x00FFFF  // Cyan
# define THEME_NEON_ELEVATION_TOP      0xFFFFFF  // White
# define THEME_NEON_FOREGROUND         0x00FFFF
# define THEME_NEON_ACCENT             0xFF1493
# define THEME_NEON_SECONDARY          0x8A2BE2
# define THEME_NEON_SPECIAL_1          0x39FF14  // Electric lime
# define THEME_NEON_SPECIAL_2          0xFF073A  // Electric red

// User can easily add more themes here following the same pattern...

/* ************************************************************************** */
/*                          THEME BEHAVIOR SETTINGS                          */
/* ************************************************************************** */

/* ************************************************************************** */
/* THEMES                                                                     */
/* ************************************************************************** */

// Default Theme - Clean and minimal
# define THEME_DEFAULT_BACKGROUND      0x151515
# define THEME_DEFAULT_GROUND          0x333333
# define THEME_DEFAULT_DEFAULT         0xFFFFFF
# define THEME_DEFAULT_DEPTH_BOTTOM    0x000033
# define THEME_DEFAULT_DEPTH_LOW       0x003366
# define THEME_DEFAULT_MIDDLE          0x666666
# define THEME_DEFAULT_ELEVATION_MID   0x999999
# define THEME_DEFAULT_ELEVATION_HIGH  0xCCCCCC
# define THEME_DEFAULT_ELEVATION_TOP   0xFFFFFF
# define THEME_DEFAULT_FOREGROUND      0xEAEAEA
# define THEME_DEFAULT_ACCENT          0xF3AF3D
# define THEME_DEFAULT_SECONDARY       0x202020
# define THEME_DEFAULT_SPECIAL_1       0x4A90E2
# define THEME_DEFAULT_SPECIAL_2       0x7ED321

// Earth Theme - Natural terrain colors
# define THEME_EARTH_BACKGROUND        0x87CEEB
# define THEME_EARTH_GROUND            0x8B7355
# define THEME_EARTH_DEFAULT           0x90EE90
# define THEME_EARTH_DEPTH_BOTTOM      0x000080  // Deep ocean
# define THEME_EARTH_DEPTH_LOW         0x4169E1  // Shallow water
# define THEME_EARTH_MIDDLE            0x90EE90  // Sea level/grass
# define THEME_EARTH_ELEVATION_MID     0x228B22  // Forest
# define THEME_EARTH_ELEVATION_HIGH    0x8B4513  // Mountain
# define THEME_EARTH_ELEVATION_TOP     0xFFFFFF  // Snow caps
# define THEME_EARTH_FOREGROUND        0x2F4F4F
# define THEME_EARTH_ACCENT            0x32CD32
# define THEME_EARTH_SECONDARY         0x556B2F
# define THEME_EARTH_SPECIAL_1         0xFFA500  // Sunset
# define THEME_EARTH_SPECIAL_2         0x87CEEB  // Sky

// Fire Theme - Heat and energy
# define THEME_FIRE_BACKGROUND         0x000000
# define THEME_FIRE_GROUND             0x330000
# define THEME_FIRE_DEFAULT            0xFF4500
# define THEME_FIRE_DEPTH_BOTTOM       0x000000  // Cold/black
# define THEME_FIRE_DEPTH_LOW          0x8B0000  // Dark red
# define THEME_FIRE_MIDDLE             0xFF4500  // Orange red
# define THEME_FIRE_ELEVATION_MID      0xFF8C00  // Dark orange
# define THEME_FIRE_ELEVATION_HIGH     0xFFD700  // Gold
# define THEME_FIRE_ELEVATION_TOP      0xFFFFE0  // Light yellow
# define THEME_FIRE_FOREGROUND         0xFFE4E1
# define THEME_FIRE_ACCENT             0xFF6347
# define THEME_FIRE_SECONDARY          0x8B0000
# define THEME_FIRE_SPECIAL_1          0xFF1493  // Hot pink
# define THEME_FIRE_SPECIAL_2          0x00FF00  // Contrast green

// Ocean Theme - Deep sea colors
# define THEME_OCEAN_BACKGROUND        0x000033
# define THEME_OCEAN_GROUND            0x191970
# define THEME_OCEAN_DEFAULT           0x4682B4
# define THEME_OCEAN_DEPTH_BOTTOM      0x000033  // Abyss
# define THEME_OCEAN_DEPTH_LOW         0x191970  // Deep blue
# define THEME_OCEAN_MIDDLE            0x4682B4  // Steel blue
# define THEME_OCEAN_ELEVATION_MID     0x87CEEB  // Sky blue
# define THEME_OCEAN_ELEVATION_HIGH    0xB0E0E6  // Powder blue
# define THEME_OCEAN_ELEVATION_TOP     0xF0F8FF  // Alice blue
# define THEME_OCEAN_FOREGROUND        0xE0FFFF
# define THEME_OCEAN_ACCENT            0x00CED1
# define THEME_OCEAN_SECONDARY         0x2F4F4F
# define THEME_OCEAN_SPECIAL_1         0x7FFFD4  // Aquamarine
# define THEME_OCEAN_SPECIAL_2         0xFF6347  // Coral

// Neon Theme - Cyberpunk aesthetic
# define THEME_NEON_BACKGROUND         0x0A0A0A
# define THEME_NEON_GROUND             0x1A0033
# define THEME_NEON_DEFAULT            0xFF00FF
# define THEME_NEON_DEPTH_BOTTOM       0x000000  // Black
# define THEME_NEON_DEPTH_LOW          0x4B0082  // Indigo
# define THEME_NEON_MIDDLE             0xFF00FF  // Magenta
# define THEME_NEON_ELEVATION_MID      0x00FF00  // Lime
# define THEME_NEON_ELEVATION_HIGH     0x00FFFF  // Cyan
# define THEME_NEON_ELEVATION_TOP      0xFFFFFF  // White
# define THEME_NEON_FOREGROUND         0x00FFFF
# define THEME_NEON_ACCENT             0xFF1493
# define THEME_NEON_SECONDARY          0x8A2BE2
# define THEME_NEON_SPECIAL_1          0x39FF14  // Electric lime
# define THEME_NEON_SPECIAL_2          0xFF073A  // Electric red

// User can easily add more themes here following the same pattern...

/* ************************************************************************** */
/*                          THEME BEHAVIOR SETTINGS                          */
/* ************************************************************************** */

// Default theme behavior
# define DEFAULT_GRADIENT_STEPS        256
# define DEFAULT_USE_SMOOTH           1
# define DEFAULT_CONTRAST             1.0f
# define DEFAULT_BRIGHTNESS           0.0f

// Advanced users can customize interpolation behavior
# define ENABLE_HDR_COLORS            0     // High dynamic range colors
# define ENABLE_COLOR_DITHERING       0     // Dithering for smooth gradients
# define ENABLE_GAMMA_CORRECTION      1     // Gamma correction for better perception

#endif
