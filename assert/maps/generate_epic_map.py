import math
import random

# Size of the map
SIZE = 100

# Create the map file
with open('epic_landscape.fdf', 'w') as f:
    for y in range(SIZE):
        line = []
        for x in range(SIZE):
            # Base terrain - large mountains
            base = 10 * math.sin(x/8) * math.cos(y/8)
            
            # Add a central volcano/crater
            center_x, center_y = SIZE/2, SIZE/2
            dist_from_center = math.sqrt((x - center_x)**2 + (y - center_y)**2)
            crater = 0
            if dist_from_center < 25:
                crater = 15 * (1 - dist_from_center/25) * math.cos(dist_from_center/2)
            
            # Add fractal-like ridges
            ridges = 6 * math.sin(x/3 + y/5) * math.cos(x/4 - y/3)
            
            # Add smaller terrain details
            detail = 2 * math.sin(x/2) * math.sin(y/2)
            
            # Add spiral pattern
            angle = math.atan2(y - center_y, x - center_x)
            spiral = 5 * math.sin(8 * angle + dist_from_center/3)
            
            # Add noise for natural look
            noise = random.uniform(-1, 1)
            
            # Combine all elements with different weights
            height = int(base + crater + ridges + detail + spiral + noise)
            
            # Add color for specific heights (optional)
            color = ""
            if height > 15:
                color = ",0xFF0000"  # Red for high peaks
            elif height < -15:
                color = ",0x0000FF"  # Blue for deep valleys
            elif abs(height) < 2:
                color = ",0x00FF00"  # Green for flat areas
                
            line.append(str(height) + color)
        f.write(' '.join(line) + '\n')

print("Epic landscape map generated!")
