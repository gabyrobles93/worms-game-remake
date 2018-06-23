#ifndef __CLIENT_SETTINGS_H__
#define __CLIENT_SETTINGS_H__

#define RESOLUTION_HIGH_DEFAULT 760
#define RESOLUTION_WIDTH_DEFAULT 1024
#define SOUND_FX_DEFAULT 1
#define FULL_SCREEN_DEFAULT 1

class ClientSettings {
    public:
        ClientSettings(void);

        int RESOLUTION_HIGH;
        int RESOLUTION_WIDTH;
        bool SOUND_FX;
        bool FULL_SCREEN;
};

#endif