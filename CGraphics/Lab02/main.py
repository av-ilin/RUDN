import pygame as pg
from constants import *
from figure import Figure3D

pg.init()
screen = pg.display.set_mode((WIDTH, HEIGHT))
pg.display.set_caption("Figure3D")
clock = pg.time.Clock()

fig = Figure3D('config/config_cube')
fig.update(screen)

running = True
while running:
    clock.tick(FPS)
    for event in pg.event.get():
        if event.type == pg.QUIT:
            running = False

        if pg.key.get_pressed()[KEY_W]:
            fig.update(screen, d_fi=SPEED)
        if pg.key.get_pressed()[KEY_S]:
            fig.update(screen, d_fi=-SPEED)
        if pg.key.get_pressed()[KEY_A]:
            fig.update(screen, d_theta=SPEED)
        if pg.key.get_pressed()[KEY_D]:
            fig.update(screen, d_theta=-SPEED)
        if pg.key.get_pressed()[KEY_Q]:
            fig.update(screen, d_zoom=-1)
        if pg.key.get_pressed()[KEY_E]:
            fig.update(screen, d_zoom=1)

        if pg.key.get_pressed()[KEY_SHIFT] and pg.key.get_pressed()[KEY_Z]:
            fig.update(screen, d_alpha=-SPEED)
        elif pg.key.get_pressed()[KEY_Z]:
            fig.update(screen, d_alpha=SPEED)
        if pg.key.get_pressed()[KEY_SHIFT] and pg.key.get_pressed()[KEY_X]:
            fig.update(screen, d_gamma=-SPEED)
        elif pg.key.get_pressed()[KEY_X]:
            fig.update(screen, d_gamma=SPEED)
        if pg.key.get_pressed()[KEY_SHIFT] and pg.key.get_pressed()[KEY_C]:
            fig.update(screen, d_beta=-SPEED)
        elif pg.key.get_pressed()[KEY_C]:
            fig.update(screen, d_beta=SPEED)

    pg.display.update()
    pg.display.flip()

pg.quit()