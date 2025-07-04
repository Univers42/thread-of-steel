/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_destroy_image.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:37:37 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/04 17:37:47 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"mlx_int.h"

/**
 * mlx_destroy_image - Destroy an image and free its resources.
 * @param xvar Pointer to the X server connection structure.
 * @param img Pointer to the image structure to be destroyed.
 * @return 0 on success, or -1 on failure.
 * @note This function frees the memory associated with the image,
 * including its data, pixmap, and graphics context (GC).
 * If the image was created using shared memory (XShm), it detaches
 * from the shared memory segment and frees it as well.
 */
int	mlx_destroy_image(t_xvar *xvar, t_img *img)
{
  if (img->type == MLX_TYPE_SHM_PIXMAP ||
      img->type == MLX_TYPE_SHM)
    {
      XShmDetach(xvar->display, &(img->shm));
      shmdt(img->shm.shmaddr);
      /* shmctl IPC_RMID already done */
    }
  XDestroyImage(img->image);  /* For image & shm-image. Also free img->data */
  XFreePixmap(xvar->display, img->pix);
  if (img->gc)
    XFreeGC(xvar->display, img->gc);
  free(img);
  if (xvar->do_flush)
    XFlush(xvar->display);
}
