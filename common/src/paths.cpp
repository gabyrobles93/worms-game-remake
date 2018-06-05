#include "paths.h"

Paths::Paths(const char * r) {
  std::string root;
  if (r) {
    root = r;
  } else {
    root = "../../";
  }

  /* GIRDERS PATHS */
  // Long
  this->PATH_GIRDER_LONG_90 = root + "resources/graphics/Weapons/grdl0.png";
  this->PATH_GIRDER_LONG_60 = root + "resources/graphics/Weapons/grdl1.png";
  this->PATH_GIRDER_LONG_45 = root + "resources/graphics/Weapons/grdl2.png";
  this->PATH_GIRDER_LONG_30 = root + "resources/graphics/Weapons/grdl3.png";
  this->PATH_GIRDER_LONG_0 = root + "resources/graphics/Weapons/grdl4.png";
  this->PATH_GIRDER_LONG_NEGATIVE_30 = root + "resources/graphics/Weapons/grdl5.png";
  this->PATH_GIRDER_LONG_NEGATIVE_45 = root + "resources/graphics/Weapons/grdl6.png";
  this->PATH_GIRDER_LONG_NEGATIVE_60 = root + "resources/graphics/Weapons/grdl7.png";
  this->PATH_GIRDER_LONG_NEGATIVE_90 = root + "resources/graphics/Weapons/grdl8.png";

  // Short
  this->PATH_GIRDER_SHORT_90 = root + "resources/graphics/Weapons/grds0.png";
  this->PATH_GIRDER_SHORT_60 = root + "resources/graphics/Weapons/grds1.png";
  this->PATH_GIRDER_SHORT_45 = root + "resources/graphics/Weapons/grds2.png";
  this->PATH_GIRDER_SHORT_30 = root + "resources/graphics/Weapons/grds3.png";
  this->PATH_GIRDER_SHORT_0 = root + "resources/graphics/Weapons/grds4.png";
  this->PATH_GIRDER_SHORT_NEGATIVE_30 = root + "resources/graphics/Weapons/grds5.png";
  this->PATH_GIRDER_SHORT_NEGATIVE_45 = root + "resources/graphics/Weapons/grds6.png";
  this->PATH_GIRDER_SHORT_NEGATIVE_60 = root + "resources/graphics/Weapons/grds7.png";
  this->PATH_GIRDER_SHORT_NEGATIVE_90 = root + "resources/graphics/Weapons/grds8.png";
  /* ------------------------------ */

  /* WORM PATHS */
  this->PATH_PLAIN_WORM = root + "resources/graphics/Worms/plain_worm.png";
  this->PATH_WORM_BREATH_1 = root + "resources/graphics/Worms/wbrth1.png";
  this->PATH_WORM_BREATH_1_UP = root + "resources/graphics/Worms/wbrth1u.png";
  this->PATH_WORM_BREATH_1_DOWN = root + "resources/graphics/Worms/wbrth1d.png";
  this->PATH_WORM_WALK = root + "resources/graphics/Worms/wwalk.png";
  this->PATH_WORM_WALK_UP = root + "resources/graphics/Worms/wwalku.png";
  this->PATH_WORM_WALK_DOWN = root + "resources/graphics/Worms/wwalkd.png";
  this->PATH_WORM_ROLL = root + "resources/graphics/Worms/wroll.png";
  this->PATH_WORM_FALL_DN = root + "resources/graphics/Worms/wfall.png";
  this->PATH_WORM_JUMP = root + "resources/graphics/Worms/wjump.jpg";
  /* ----------------------------------- */

  /* WATER PATHS */
  this->PATH_WATER_DEFAULT = root + "resources/graphics/water_gif.gif";
  this->PATH_WATER_2 = root + "resources/graphics/water_pattern_2.png";
  this->PATH_WATER_3 = root + "resources/graphics/water_pattern_3.png";
  this->PATH_LAVA = root + "resources/graphics/lava_pattern.jpg";
  /* --------------------------- */


  /* WEAPON ICONS */
  this->PATH_ICON_BAZOOKA = root + "resources/graphics/Weapon Icons/bazooka.1.png";
  this->PATH_ICON_MORTAR = root + "resources/graphics/Weapon Icons/mortar.1.png";
  this->PATH_ICON_GREEN_GRENADE = root + "resources/graphics/Weapon Icons/grenade.1.png";
  this->PATH_ICON_RED_GRENADE = root + "resources/graphics/Weapon Icons/cluster.1.png";
  this->PATH_ICON_BANANA = root + "resources/graphics/Weapon Icons/banana.1.png";
  this->PATH_ICON_HOLY_GRENADE = root + "resources/graphics/Weapon Icons/hgrenade.1.png";
  this->PATH_ICON_DYNAMITE = root + "resources/graphics/Weapon Icons/dynamite.1.png";
  this->PATH_ICON_BASEBALL = root + "resources/graphics/Weapon Icons/baseball.1.png";
  this->PATH_ICON_AIR_STRIKE = root + "resources/graphics/Weapon Icons/airstrke.1.png";
  this->PATH_ICON_TELEPORT = root + "resources/graphics/Weapon Icons/teleport.1.png";
  this->PATH_ICON_SHORT_GIRDER = root + "resources/graphics/Weapon Icons/girder.2.png";
  this->PATH_ICON_LONG_GIRDER = root + "resources/graphics/Weapon Icons/girders.1.png";
  /* ------------- */

  /* WEAPONS */
  this->PATH_DYNAMITE = root + "resources/graphics/Weapons/dynamite.png";
  /* ------------- */

  /* EFFECTS */
  this->PATH_EXPLOSION_EFFECT = root + "resources/graphics/Effects/firehit.png";
  this->PATH_DEFAULT_SIGHT = root + "resources/graphics/Misc/crshairr.png";
  /* ---------------------------- */

  /* FONTS */
  this->PATH_FONT_WORM_DATA = root + "resources/fonts/arial.ttf";
  this->PATH_FONT_GROBOLD = root + "resources/fonts/GROBOLD.ttf";
  this->PATH_FONT_VERDANA_BOLD = root + "resources/fonts/verdanab.ttf";
  this->PATH_FONT_ARIAL_BOLD = root + "resources/fonts/arialb.ttf";

  /* SOUND_EFFECTS */
  this->PATH_SOUND_DYNAMITE = root + "resources/sounds/Effects/FUSE.WAV";
  this->PATH_SOUND_GIRDER = root + "resources/sounds/Effects/GIRDERIMPACT.WAV";
  this->PATH_SOUND_TELEPORT = root + "resources/sounds/Effects/TELEPORT.WAV";
  // Explosions
  this->PATH_SOUND_EXPLOSION_1 = root + "resources/sounds/Effects/Explosion1.wav";
  this->PATH_SOUND_EXPLOSION_2 = root + "resources/sounds/Effects/Explosion2.wav";
  this->PATH_SOUND_EXPLOSION_3 = root + "resources/sounds/Effects/Explosion3.wav";
  /* -------------- */
}