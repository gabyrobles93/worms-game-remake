#ifndef __PATHS_H__
#define __PATHS_H__

#include <string>

class Paths {
  public:
    /* GIRDERS PATHS */
    // Long
    std::string PATH_GIRDER_LONG_90;
    std::string PATH_GIRDER_LONG_60;
    std::string PATH_GIRDER_LONG_45;
    std::string PATH_GIRDER_LONG_30;
    std::string PATH_GIRDER_LONG_0;
    std::string PATH_GIRDER_LONG_NEGATIVE_30;
    std::string PATH_GIRDER_LONG_NEGATIVE_45;
    std::string PATH_GIRDER_LONG_NEGATIVE_60;
    std::string PATH_GIRDER_LONG_NEGATIVE_90;

    // Short
    std::string PATH_GIRDER_SHORT_90;
    std::string PATH_GIRDER_SHORT_60;
    std::string PATH_GIRDER_SHORT_45;
    std::string PATH_GIRDER_SHORT_30;
    std::string PATH_GIRDER_SHORT_0;
    std::string PATH_GIRDER_SHORT_NEGATIVE_30;
    std::string PATH_GIRDER_SHORT_NEGATIVE_45;
    std::string PATH_GIRDER_SHORT_NEGATIVE_60;
    std::string PATH_GIRDER_SHORT_NEGATIVE_90;
    /* ------------------------------ */

    /* WORM PATHS */
    std::string PATH_PLAIN_WORM;
    std::string PATH_WORM_BREATH_1;
    std::string PATH_WORM_BREATH_1_UP;
    std::string PATH_WORM_BREATH_1_DOWN;
    std::string PATH_WORM_WALK;
    std::string PATH_WORM_WALK_UP;
    std::string PATH_WORM_WALK_DOWN;
    std::string PATH_WORM_ROLL;
    std::string PATH_WORM_FALL_DN;
    std::string PATH_WORM_JUMP;
    /* ----------------------------------- */

    /* WATER PATHS */
    std::string PATH_WATER_DEFAULT;
    std::string PATH_WATER_2;
    std::string PATH_WATER_3;
    std::string PATH_LAVA;
    /* --------------------------- */


    /* WEAPON ICONS */
    std::string PATH_ICON_BAZOOKA;
    std::string PATH_ICON_MORTAR;
    std::string PATH_ICON_GREEN_GRENADE;
    std::string PATH_ICON_RED_GRENADE;
    std::string PATH_ICON_BANANA;
    std::string PATH_ICON_HOLY_GRENADE;
    std::string PATH_ICON_DYNAMITE;
    std::string PATH_ICON_BASEBALL;
    std::string PATH_ICON_AIR_STRIKE;
    std::string PATH_ICON_TELEPORT;
    std::string PATH_ICON_SHORT_GIRDER;
    std::string PATH_ICON_LONG_GIRDER;
    /* ------------- */

    /* WEAPONS */
    std::string PATH_DYNAMITE;
    /* ---------------------------- */

    /* FONTS */
    std::string PATH_FONT_WORM_DATA;
    std::string PATH_FONT_GROBOLD;
    std::string PATH_FONT_VERDANA_BOLD;
    std::string PATH_FONT_ARIAL_BOLD;

    Paths(const char * r = NULL);


};

extern Paths gPath;

#endif