import pygame as pg
from constants import *
from figure import Figure3D


def hello():
    print('Figure:')
    print('0.Cube')
    print('1.Pyramid')
    print('2.Parallelepiped')
    return int(input('Your choose: '))


user_choose = hello()
user_choose = user_choose if user_choose < 3 else 0

pg.init()
screen = pg.display.set_mode((WIDTH, HEIGHT))
pg.display.set_caption("Figure3D")
clock = pg.time.Clock()

fig = Figure3D(CONFIGS[user_choose])
fig.update(screen)

running = True
while running:
    clock.tick(FPS)
    for event in pg.event.get():
        if event.type == pg.QUIT:
            running = False

        if event.type == pg.KEYDOWN:
            if event.key == KEY_TAB:
                fig.change_view_mode()
                fig.update(screen)

        if event.type == pg.KEYDOWN:
            if event.key == KEY_CTRL:
                fig.change_algorithm()
                fig.update(screen)

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
