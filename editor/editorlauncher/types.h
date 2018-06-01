#ifndef __COMMON_TYPES_H__
#define __COMMON_TYPES_H__

/*
 Se definen tipos de datos comunes al cliente y el servidor.
*/
typedef enum {
    a_noEvent,
    a_moveLeft,
    a_moveRight,
    a_stopMoving,
    a_pointUp,
    a_pointDown,
    a_shoot,
    a_frontJump,
    a_backJump,
    a_selectWeapon,
    a_pointFlyShoot,
    a_choose1SecDeton,
    a_choose2SecDeton,
    a_choose3SecDeton,
    a_choose4SecDeton,
    a_choose5SecDeton,
    a_showWeaponMenu,
    a_changeWorm,
    a_quitGame
} action_t;

typedef enum {
    w_bazooka,
    w_mortar,
    w_red_bomb,
    w_banana,
    w_green_bomb,
    w_holy_bomb,
    w_dynamite,
    w_fly_bomb,
    w_teleport,
    w_bat
} weapon_t;

typedef unsigned char uchar;

#endif
