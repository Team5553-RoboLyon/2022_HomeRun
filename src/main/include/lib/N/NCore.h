#ifndef __NCORE_H
#define __NCORE_H

#include "lib/N/NType.h"
#include "lib/N/NFlags.h"

#ifdef __cplusplus
extern "C"
{
#endif
    extern Nu32 NEngineCoreFlags;
    // PRIVATE Engine Flags
// BIT_0 to BIT_1 included need to set as they are because they are linked with File system flags !!!
#define FLAG_NENGINE_CORE_FILESYSTEM_APP_ROOT_RELATIVE_PATH BIT_0 //|! At least one of the two is set to ON. If both are set to ON that means AUTO EVALUATE THE BEST SOLUTION PATH by PATH
#define FLAG_NENGINE_CORE_FILESYSTEM_FULL_PATH BIT_1              //|! NEED TO STAY BIT_0 and BIT_1 Like FLAG_NFILE_APP_ROOT_RELATIVE_PATH and FLAG_NENGINE_CORE_FILESYSTEM_FULL_PATH !

#define FLAG_NENGINE_CORE_CONTINUE BIT_2
#define FLAG_NENGINE_CORE_RENDERING BIT_3
#define FLAG_NENGINE_CORE_UPDATE_TRANSFORMATION_TREE BIT_4

#define FLAG_NENGINE_CORE_PAUSE_PARTICLES BIT_5
#define FLAG_NENGINE_CORE_PAUSE_PHYSIC BIT_6
#define FLAG_NENGINE_CORE_AUDIO_XRAM BIT_7  // ON if Audio XRAM extension is supported by hardware ("NAudio_Init" has to be called)
#define FLAG_NENGINE_CORE_AUDIO_EFX BIT_8   // ON if Audio EFX extension is supported by hardware ("NAudio_Init" has to be called)
#define FLAG_NENGINE_CORE_AUDIO_MUTED BIT_9 // ON NAudio system is muted OFF is Not

#define FLAG_NENGINE_CORE_BLOCK_EVENT_TO_GAMESTATES BIT_10 // Set to ON. Event To GameStates Dispatch is blocked.
#define FLAG_NENGINE_CORE_BLOCK_EVENT_TO_UI BIT_11         // Set to ON. Event To UI Dispatch is blocked.
#define FLAG_NENGINE_CORE_HIERARCHY_CAPTURE_TOUCH_MOVE_IN BIT_12
#define FLAG_NENGINE_CORE_GAMESATE_TOUCH_MOVE_ADVANCED_DISPATCH BIT_13
#define FLAG_NENGINE_CORE_TIMERSTACK_TO_BE_CLEAN BIT_14

#ifdef _NEDITOR
#define FLAG_NENGINE_CORE_EDITOR_INITIALIZED BIT_15
#endif
#define FLAG_NENGINE_CORE_GL_INITIALIZED BIT_16
#define FLAG_NENGINE_CORE_INITIALIZED BIT_17

// -------------------------------------------------------------------------------------------------
#define FLAG_NENGINE_CORE_AD_REWARDED_LOADED BIT_30
#define FLAG_NENGINE_CORE_AD_INTERSTITIAL_LOADED BIT_31

// -----------------------------
// BIT_0 to BIT_1 included need to set as they are because they are linked with File system flags !!!
#define MASK_NENGINE_CORE_PATH_FILESYSTEM (FLAG_NENGINE_CORE_FILESYSTEM_APP_ROOT_RELATIVE_PATH | FLAG_NENGINE_CORE_FILESYSTEM_FULL_PATH)
// -----------------------------
#define MASK_NENGINE_CORE_EVENT_TO_GAMESTATES_BLOCKING (FLAG_NENGINE_CORE_BLOCK_EVENT_TO_GAMESTATES)
#define MASK_NENGINE_CORE_EVENT_TO_UI_BLOCKING (FLAG_NENGINE_CORE_BLOCK_EVENT_TO_UI)

    extern Nu32 NEngineCoreFlags;

    inline void NSwitchToFullPathFileSystem()
    {
        FLAG_ON(NEngineCoreFlags, FLAG_NENGINE_CORE_FILESYSTEM_FULL_PATH);
        FLAG_OFF(NEngineCoreFlags, FLAG_NENGINE_CORE_FILESYSTEM_APP_ROOT_RELATIVE_PATH);
    }
    inline void NSwitchToRootRelativePathFileSystem()
    {
        FLAG_OFF(NEngineCoreFlags, FLAG_NENGINE_CORE_FILESYSTEM_FULL_PATH);
        FLAG_ON(NEngineCoreFlags, FLAG_NENGINE_CORE_FILESYSTEM_APP_ROOT_RELATIVE_PATH);
    }
    inline void NSwitchToAutoPathFileSystem()
    {
        FLAG_ON(NEngineCoreFlags, FLAG_NENGINE_CORE_FILESYSTEM_FULL_PATH);
        FLAG_ON(NEngineCoreFlags, FLAG_NENGINE_CORE_FILESYSTEM_APP_ROOT_RELATIVE_PATH);
    }

#ifdef __cplusplus
}
#endif // __cpluplus
#endif // __NCORE_H