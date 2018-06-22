#include "paths.h"

Paths::Paths(const char * r) {
  if (r) {
    this->root = r;
  } else {
    this->root = "../../";
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
  this->PATH_GREEN_GRENADE = root + "resources/graphics/Weapons/grenade.png";
  this->PATH_HOLY_GRENADE = root + "resources/graphics/Weapons/hgrenade.png";
  this->PATH_BANANA = root + "resources/graphics/Weapons/banana.png";
  this->PATH_BAZOOKA = root + "resources/graphics/Weapons/missile.png";
  this->PATH_AIR_STRIKE = root + "resources/graphics/Weapons/airmisil.png";
  this->PATH_CLUSTER = root + "resources/graphics/Weapons/cluster.png";
  this->PATH_MORTAR = root + "resources/graphics/Weapons/mortar.png";
  /* ----------------------------------- */

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
  this->PATH_WORM_FLYING_1 = root + "resources/graphics/Worms/wfly1.png";
  this->PATH_WORM_FLYING_2 = root + "resources/graphics/Worms/wfly2.png";
  this->PATH_WORM_FLYING_3 = root + "resources/graphics/Worms/wfly3.png";
  this->PATH_WORM_DIE = root + "resources/graphics/Worms/wdie.png";

    // Pick weapons
    this->PATH_WORM_PICK_BAZOOKA = root + "resources/graphics/Worms/wbazlnk.png";
    this->PATH_WORM_PICK_BAZOOKA_UP = root + "resources/graphics/Worms/wbazlnku.png";
    this->PATH_WORM_PICK_BAZOOKA_DOWN = root + "resources/graphics/Worms/wbazlnkd.png";
    this->PATH_WORM_PICK_MORTAR = root + "resources/graphics/Worms/wbz2lnk.png";;
    this->PATH_WORM_PICK_MORTAR_UP = root + "resources/graphics/Worms/wbz2lnku.png";;
    this->PATH_WORM_PICK_MORTAR_DOWN = root + "resources/graphics/Worms/wbz2lnkd.png";;
    this->PATH_WORM_PICK_GREEN_GRENADE = root + "resources/graphics/Worms/wgrnlnk.png";
    this->PATH_WORM_PICK_GREEN_GRENADE_UP = root + "resources/graphics/Worms/wgrnlnku.png";
    this->PATH_WORM_PICK_GREEN_GRENADE_DOWN = root + "resources/graphics/Worms/wgrnlnkd.png";
    this->PATH_WORM_PICK_CLUSTER = root + "resources/graphics/Worms/wclslnk.png";
    this->PATH_WORM_PICK_CLUSTER_UP = root + "resources/graphics/Worms/wclslnku.png";
    this->PATH_WORM_PICK_CLUSTER_DOWN = root + "resources/graphics/Worms/wclslnkd.png";
    this->PATH_WORM_PICK_BANANA = root + "resources/graphics/Worms/wbanlnk.png";
    this->PATH_WORM_PICK_BANANA_UP = root + "resources/graphics/Worms/wbanlnku.png";
    this->PATH_WORM_PICK_BANANA_DOWN = root + "resources/graphics/Worms/wbanlnkd.png";
    this->PATH_WORM_PICK_HOLY_GRENADE = root + "resources/graphics/Worms/whgrlnk.png";
    this->PATH_WORM_PICK_HOLY_GRENADE_UP = root + "resources/graphics/Worms/whgrlnku.png";
    this->PATH_WORM_PICK_HOLY_GRENADE_DOWN = root + "resources/graphics/Worms/whgrlnkd.png";
    this->PATH_WORM_PICK_AIR_STRIKE = root + "resources/graphics/Worms/wairlnk.png";
    this->PATH_WORM_PICK_AIR_STRIKE_UP = root + "resources/graphics/Worms/wairbaku.png";
    this->PATH_WORM_PICK_AIR_STRIKE_DOWN = root + "resources/graphics/Worms/wairbakd.png";
    this->PATH_WORM_PICK_DYNAMITE = root + "resources/graphics/Worms/wdynlnk.png";
    this->PATH_WORM_PICK_DYNAMITE_UP = root + "resources/graphics/Worms/wdynlnku.png";
    this->PATH_WORM_PICK_DYNAMITE_DOWN = root + "resources/graphics/Worms/wdynlnkd.png";
    this->PATH_WORM_PICK_BASEBALL = root + "resources/graphics/Worms/wbsblnk.png";
    this->PATH_WORM_PICK_BASEBALL_UP = root + "resources/graphics/Worms/wbsblnku.png";
    this->PATH_WORM_PICK_BASEBALL_DOWN = root + "resources/graphics/Worms/wbsblnkd.png";
    this->PATH_WORM_PICK_TELEPORT = root + "resources/graphics/Worms/wtellnk.png";
    this->PATH_WORM_PICK_TELEPORT_UP = root + "resources/graphics/Worms/wtellnku.png";
    this->PATH_WORM_PICK_TELEPORT_DOWN = root + "resources/graphics/Worms/wtellnkd.png";

    // Hide weapons
    this->PATH_WORM_HIDE_BAZOOKA = root + "resources/graphics/Worms/wbazbak.png";
    this->PATH_WORM_HIDE_BAZOOKA_UP = root + "resources/graphics/Worms/wbazbaku.png";
    this->PATH_WORM_HIDE_BAZOOKA_DOWN = root + "resources/graphics/Worms/wbazbakd.png";
    this->PATH_WORM_HIDE_MORTAR = root + "resources/graphics/Worms/wbz2bak.png";
    this->PATH_WORM_HIDE_MORTAR_UP = root + "resources/graphics/Worms/wbz2baku.png";
    this->PATH_WORM_HIDE_MORTAR_DOWN = root + "resources/graphics/Worms/wbz2bakd.png";
    this->PATH_WORM_HIDE_GREEN_GRENADE = root + "resources/graphics/Worms/wgrnbak.png";
    this->PATH_WORM_HIDE_GREEN_GRENADE_UP = root + "resources/graphics/Worms/wgrnbaku.png";
    this->PATH_WORM_HIDE_GREEN_GRENADE_DOWN = root + "resources/graphics/Worms/wgrnbakd.png";
    this->PATH_WORM_HIDE_CLUSTER = root + "resources/graphics/Worms/wclsbak.png";
    this->PATH_WORM_HIDE_CLUSTER_UP = root + "resources/graphics/Worms/wclsbaku.png";
    this->PATH_WORM_HIDE_CLUSTER_DOWN = root + "resources/graphics/Worms/wclsbakd.png";
    this->PATH_WORM_HIDE_BANANA = root + "resources/graphics/Worms/wbanbak.png";
    this->PATH_WORM_HIDE_BANANA_UP = root + "resources/graphics/Worms/wbanbaku.png";
    this->PATH_WORM_HIDE_BANANA_DOWN = root + "resources/graphics/Worms/wbanbakd.png";
    this->PATH_WORM_HIDE_HOLY_GRENADE = root + "resources/graphics/Worms/whgrbak.png";
    this->PATH_WORM_HIDE_HOLY_GRENADE_UP = root + "resources/graphics/Worms/whgrbaku.png";
    this->PATH_WORM_HIDE_HOLY_GRENADE_DOWN = root + "resources/graphics/Worms/whgrbakd.png";
    this->PATH_WORM_HIDE_DYNAMITE = root + "resources/graphics/Worms/wdynbak.png";
    this->PATH_WORM_HIDE_DYNAMITE_UP = root + "resources/graphics/Worms/wdynbaku.png";
    this->PATH_WORM_HIDE_DYNAMITE_DOWN = root + "resources/graphics/Worms/wdynbakd.png";
    this->PATH_WORM_HIDE_AIR_STRIKE = root + "resources/graphics/Worms/wairbak.png";
    this->PATH_WORM_HIDE_AIR_STRIKE_UP = root + "resources/graphics/Worms/wairbaku.png";
    this->PATH_WORM_HIDE_AIR_STRIKE_DOWN = root + "resources/graphics/Worms/wairbakd.png";
    this->PATH_WORM_HIDE_BASEBALL = root + "resources/graphics/Worms/wbsbbak.png";
    this->PATH_WORM_HIDE_BASEBALL_UP = root + "resources/graphics/Worms/wbsbbaku.png";
    this->PATH_WORM_HIDE_BASEBALL_DOWN = root + "resources/graphics/Worms/wbsbbakd.png";
    this->PATH_WORM_HIDE_BASEBALL_SHOOTED = root + "resources/graphics/Worms/wbsbbk2.png";
    this->PATH_WORM_HIDE_BASEBALL_SHOOTED_UP = root + "resources/graphics/Worms/wbsbbk2u.png";
    this->PATH_WORM_HIDE_BASEBALL_SHOOTED_DOWN = root + "resources/graphics/Worms/wbsbbk2d.png";
    this->PATH_WORM_HIDE_TELEPORT = root + "resources/graphics/Worms/wtelbak.png";
    this->PATH_WORM_HIDE_TELEPORT_UP = root + "resources/graphics/Worms/wtelbaku.png";
    this->PATH_WORM_HIDE_TELEPORT_DOWN = root + "resources/graphics/Worms/wtelbakd.png";

    // Pointing
    this->PATH_WORM_POINTING_BAZOOKA = root + "resources/graphics/Worms/wbaz.png";
    this->PATH_WORM_POINTING_BAZOOKA_UP = root + "resources/graphics/Worms/wbazu.png";
    this->PATH_WORM_POINTING_BAZOOKA_DOWN = root + "resources/graphics/Worms/wbazd.png";
    this->PATH_WORM_POINTING_MORTAR = root + "resources/graphics/Worms/wbaz2.png";
    this->PATH_WORM_POINTING_MORTAR_UP = root + "resources/graphics/Worms/wbaz2u.png";
    this->PATH_WORM_POINTING_MORTAR_DOWN = root + "resources/graphics/Worms/wbaz2d.png";    
    this->PATH_WORM_POINTING_GREEN_GRENADE = root + "resources/graphics/Worms/wthrgrn.png";
    this->PATH_WORM_POINTING_GREEN_GRENADE_UP = root + "resources/graphics/Worms/wthrgrnu.png";
    this->PATH_WORM_POINTING_GREEN_GRENADE_DOWN = root + "resources/graphics/Worms/wthrgrnd.png";
    this->PATH_WORM_POINTING_CLUSTER = root + "resources/graphics/Worms/wthrcls.png";
    this->PATH_WORM_POINTING_CLUSTER_UP = root + "resources/graphics/Worms/wthrclsu.png";
    this->PATH_WORM_POINTING_CLUSTER_DOWN = root + "resources/graphics/Worms/wthrclsd.png";
    this->PATH_WORM_POINTING_BANANA = root + "resources/graphics/Worms/wthrban.png";
    this->PATH_WORM_POINTING_BANANA_UP = root + "resources/graphics/Worms/wthrbanu.png";
    this->PATH_WORM_POINTING_BANANA_DOWN = root + "resources/graphics/Worms/wthrband.png";
    this->PATH_WORM_POINTING_HOLY_GRENADE = root + "resources/graphics/Worms/wthrhgr.png";
    this->PATH_WORM_POINTING_HOLY_GRENADE_UP = root + "resources/graphics/Worms/wthrhgr.png";
    this->PATH_WORM_POINTING_HOLY_GRENADE_DOWN = root + "resources/graphics/Worms/wthrhgr.png";
    this->PATH_WORM_POINTING_BASEBALL = root + "resources/graphics/Worms/wbsbaim.png";
    this->PATH_WORM_POINTING_BASEBALL_UP = root + "resources/graphics/Worms/wbsbaimu.png";
    this->PATH_WORM_POINTING_BASEBALL_DOWN = root + "resources/graphics/Worms/wbsbaimd.png";

    // Shooting
    this->PATH_WORM_SHOOTING_AIR_STRIKE = root + "resources/graphics/Worms/wairtlk.png";
    this->PATH_WORM_SHOOTING_AIR_STRIKE_UP = root + "resources/graphics/Worms/wairtlku.png";
    this->PATH_WORM_SHOOTING_AIR_STRIKE_DOWN = root + "resources/graphics/Worms/wairtlkd.png";
    this->PATH_WORM_SHOOTING_BASEBALL = root + "resources/graphics/Worms/wbsbswn.png";
    this->PATH_WORM_SHOOTING_BASEBALL_UP = root + "resources/graphics/Worms/wbsbswnu.png";
    this->PATH_WORM_SHOOTING_BASEBALL_DOWN = root + "resources/graphics/Worms/wbsbswnd.png";
    
  /* ----------------------------------- */

  /* EFFECTS */
  this->PATH_EXPLOSION_EFFECT = root + "resources/graphics/Effects/firehit.png";
  this->PATH_DEFAULT_SIGHT = root + "resources/graphics/Misc/crshairr.png";
  this->PATH_WIND_LEFT = root + "resources/graphics/Misc/windl.png";
  this->PATH_WIND_RIGHT = root + "resources/graphics/Misc/windr.png";
  this->PATH_GRAVE_1 = root + "resources/graphics/Misc/grave1.png";
  this->PATH_GRAVE_2 = root + "resources/graphics/Misc/grave2.png";
  this->PATH_GRAVE_3 = root + "resources/graphics/Misc/grave3.png";
  this->PATH_GRAVE_4 = root + "resources/graphics/Misc/grave4.png";
  this->PATH_GRAVE_5 = root + "resources/graphics/Misc/grave5.png";
  this->PATH_GRAVE_6 = root + "resources/graphics/Misc/grave6.png";
  /* ---------------------------- */

  /* FONTS */
  this->PATH_FONT_WORM_DATA = root + "resources/fonts/arial.ttf";
  this->PATH_FONT_GROBOLD = root + "resources/fonts/GROBOLD.ttf";
  this->PATH_FONT_VERDANA_BOLD = root + "resources/fonts/verdanab.ttf";
  this->PATH_FONT_ARIAL_BOLD = root + "resources/fonts/arialb.ttf";

  /* SOUND_EFFECTS */
  this->PATH_MUSIC_DEFAULT = root + "resources/sounds/music.mp3";
  this->PATH_SOUND_DYNAMITE = root + "resources/sounds/Effects/FUSE.WAV";
  this->PATH_SOUND_GIRDER = root + "resources/sounds/Effects/GIRDERIMPACT.WAV";
  this->PATH_SOUND_TELEPORT = root + "resources/sounds/Effects/TELEPORT.WAV";
  this->PATH_SOUND_THROW_PROJECTIL = root + "resources/sounds/Effects/THROWRELEASE.WAV";
  this->PATH_SOUND_HOLY = root + "resources/sounds/Effects/HOLYGRENADE.WAV";
  this->PATH_SOUND_TIME_TRICK = root + "resources/sounds/Effects/TIMERTICK.WAV";
  this->PATH_SOUND_THROW_POWER_UP = root + "resources/sounds/Effects/THROWPOWERUP.WAV";
  this->PATH_SOUND_WORM_WALKING = root + "resources/sounds/Effects/Walk-Expand.wav";
  this->PATH_SOUND_AIR_STRIKE = root + "resources/sounds/Effects/Airstrike.wav";

    // Worms voices
    this->PATH_SOUND_LAUGH = root + "resources/sounds/Voices/Spanish/LAUGH.WAV";
    this->PATH_SOUND_FATALITY = root + "resources/sounds/Voices/Spanish/FATALITY.WAV";
    this->PATH_SOUND_HURRY = root + "resources/sounds/Voices/Spanish/HURRY.WAV";
    this->PATH_SOUND_BYE = root + "resources/sounds/Voices/Spanish/BYEBYE.WAV";
    this->PATH_SOUND_DIE = root + "resources/sounds/Voices/Spanish/OHDEAR.WAV";

    // Worms hit
    this->PATH_SOUND_NOOO = root + "resources/sounds/Voices/Spanish/NOOO.WAV";
    this->PATH_SOUND_OOFF_1 = root + "resources/sounds/Voices/Spanish/OOFF1.WAV";
    this->PATH_SOUND_OOFF_2 = root + "resources/sounds/Voices/Spanish/OOFF2.WAV";
    this->PATH_SOUND_OOFF_3 = root + "resources/sounds/Voices/Spanish/OOFF3.WAV";
    this->PATH_SOUND_OW_1 = root + "resources/sounds/Voices/Spanish/OW1.WAV";
    this->PATH_SOUND_OW_2 = root + "resources/sounds/Voices/Spanish/OW2.WAV";
    this->PATH_SOUND_OW_3 = root + "resources/sounds/Voices/Spanish/OW3.WAV";
    // About to explode
    this->PATH_SOUND_WHAT_THE = root + "resources/sounds/Voices/Spanish/WHATTHE.WAV";
    this->PATH_SOUND_UH_OH = root + "resources/sounds/Voices/Spanish/UH-OH.WAV";
    this->PATH_SOUND_TAKE_COVER = root + "resources/sounds/Voices/Spanish/TAKECOVER.WAV";
    this->PATH_SOUND_RUN_AWAY = root + "resources/sounds/Voices/Spanish/RUNAWAY.WAV";

  // Explosions
  this->PATH_SOUND_EXPLOSION_1 = root + "resources/sounds/Effects/Explosion1.wav";
  this->PATH_SOUND_EXPLOSION_2 = root + "resources/sounds/Effects/Explosion2.wav";
  this->PATH_SOUND_EXPLOSION_3 = root + "resources/sounds/Effects/Explosion3.WAV";
  /* -------------- */
}