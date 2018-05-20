#ifndef __COMMON_TYPES_H__
#define __COMMON_TYPES_H__

/*
 Se definen tipos de datos comunes al cliente y el servidor.
*/
typedef enum {
    a_noEvent,
    a_moveLeft,
    a_moveRight,
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
    a_quitGame
} action_t;

typedef unsigned char uchar;

#endif
