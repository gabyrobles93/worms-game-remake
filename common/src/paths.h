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
    std::string PATH_WORM_FLYING_1;
    std::string PATH_WORM_FLYING_2;
    std::string PATH_WORM_FLYING_3;
    std::string PATH_WORM_DIE;
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
    std::string PATH_GREEN_GRENADE;
    std::string PATH_HOLY_GRENADE;
    std::string PATH_BANANA;
    std::string PATH_BAZOOKA;
    std::string PATH_AIR_STRIKE;
    std::string PATH_CLUSTER;
    std::string PATH_MORTAR;
    /* ---------------------------- */

    /* EFFECTS */
    std::string PATH_EXPLOSION_EFFECT;
    std::string PATH_DEFAULT_SIGHT;
    std::string PATH_WIND_LEFT;
    std::string PATH_WIND_RIGHT;
    std::string PATH_GRAVE_1;
    std::string PATH_GRAVE_2;
    std::string PATH_GRAVE_3;
    std::string PATH_GRAVE_4;
    std::string PATH_GRAVE_5;
    std::string PATH_GRAVE_6;

    /* ---------------------------- */

    /* FONTS */
    std::string PATH_FONT_WORM_DATA;
    std::string PATH_FONT_GROBOLD;
    std::string PATH_FONT_VERDANA_BOLD;
    std::string PATH_FONT_ARIAL_BOLD;

    /* SOUND EFFECTS */
    std::string PATH_SOUND_DYNAMITE;
    std::string PATH_SOUND_GIRDER;
    std::string PATH_SOUND_TELEPORT;
    std::string PATH_SOUND_THROW_PROJECTIL;
    std::string PATH_SOUND_HOLY;
    std::string PATH_SOUND_THROW_POWER_UP;
    std::string PATH_SOUND_WORM_WALKING;
    std::string PATH_SOUND_AIR_STRIKE;

    std::string PATH_SOUND_TIME_TRICK;

      // Worms voices
      std::string PATH_SOUND_LAUGH;
      std::string PATH_SOUND_FATALITY;
      std::string PATH_SOUND_HURRY;
      std::string PATH_SOUND_BYE;
      std::string PATH_SOUND_DIE;

        // Worms hit
        std::string PATH_SOUND_NOOO;
        std::string PATH_SOUND_OOFF_1;
        std::string PATH_SOUND_OOFF_2;
        std::string PATH_SOUND_OOFF_3;
        std::string PATH_SOUND_OW_1;
        std::string PATH_SOUND_OW_2;
        std::string PATH_SOUND_OW_3;
        // About to explosions
        std::string PATH_SOUND_WHAT_THE;
        std::string PATH_SOUND_UH_OH;
        std::string PATH_SOUND_TAKE_COVER;
        std::string PATH_SOUND_RUN_AWAY;

    // Explosions
    std::string PATH_SOUND_EXPLOSION_1;
    std::string PATH_SOUND_EXPLOSION_2;
    std::string PATH_SOUND_EXPLOSION_3;
    /* ----------------------------- */

    Paths(const char * r = NULL);


};

extern Paths gPath;

#endif