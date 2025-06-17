#include "fdf.h"
#include "motion.h"

int handle_shape_switch(int key, int modifier, t_data *data)
{
    static t_shape_type key_shape_map[256];
    static int map_initialized = 0;
    
    if (!map_initialized) {
        // Initialize all to invalid shape
        for (int i = 0; i < 256; i++)
            key_shape_map[i] = NUM_SHAPES; // Invalid shape
        
        // Map Alt+digit keys to shapes
        key_shape_map[49] = SHAPE_TYPE_SPHERE;   // Alt+'1' -> Sphere
        key_shape_map[50] = SHAPE_TYPE_CYLINDER; // Alt+'2' -> Cylinder
        key_shape_map[51] = SHAPE_TYPE_CONE;     // Alt+'3' -> Cone
        key_shape_map[52] = SHAPE_TYPE_WAVE;     // Alt+'4' -> Wave
        key_shape_map[53] = SHAPE_TYPE_TORUS;    // Alt+'5' -> Torus
        key_shape_map[54] = SHAPE_TYPE_SADDLE;   // Alt+'6' -> Saddle
        key_shape_map[55] = SHAPE_TYPE_HELIX;    // Alt+'7' -> Helix
        key_shape_map[56] = SHAPE_TYPE_RIPPLE;   // Alt+'8' -> Ripple
        key_shape_map[57] = SHAPE_TYPE_FLAT;     // Alt+'9' -> Flat (reset)
        map_initialized = 1;
    }
    
    // Check if Alt modifier is pressed
    if (!(modifier & ALT_MASK))
        return (0);  // Not Alt+key combination
    
    // Only process if it's a valid shape key
    if (key >= 49 && key <= 57) // '1' to '9'
    {
        t_shape_type new_shape = key_shape_map[key];
        
        if (new_shape < NUM_SHAPES)
        {
            data->controls->shape_mode = new_shape;
            
            // Print shape change notification
            ft_putstr_fd("Shape changed to: ", 1);
            ft_putendl_fd((char*)get_shape_name(new_shape), 1);
            
            // Redraw with new shape
            draw_map(data);
            return (1); // Key handled
        }
    }
    
    return (0); // Key not handled
}

void cycle_shape(t_data *data)
{
    data->controls->shape_mode = (data->controls->shape_mode + 1) % NUM_SHAPES;
    
    ft_putstr_fd("Shape: ", 1);
    ft_putendl_fd((char*)get_shape_name(data->controls->shape_mode), 1);
    
    draw_map(data);
}
