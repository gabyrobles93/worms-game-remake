#ifndef __COMMON_TYPES_H__
#define __COMMON_TYPES_H__

/*
 Se definen tipos de datos comunes al cliente y el servidor.
*/
typedef enum {
    a_noEvent,
    a_refreshLobby,
    a_createMatch,
    a_quitLobby,
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
    w_cluster,
    w_green_grenade,
    w_banana,
    w_holy_grenade,
    w_air_strike,
    w_dynamite,
    w_bat,
    w_teleport
} weapon_t;

typedef enum {
    quited,
    lobby,
    joined,
    creator,
    on_match
} client_status_t;

typedef unsigned char uchar;

#endif
