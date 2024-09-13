        // Draw the vertical line (wall)
        for (int y = ray->draw_start; y < ray->draw_end; y++)
        {
            ray->addr[y * ray->line_length / 4 + x] = color;  // Write to the memory image
        }
//dont fully understand this part lodev use thi sin C++ instead:

      //draw the pixels of the stripe as a vertical line
      verLine(x, drawStart, drawEnd, color);
    }

see what mlx func use fro refresh the game, like what image put use windows or only image