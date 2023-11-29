#ifndef INTERFACECONTROLLER_HPP
#define INTERFACECONTROLLER_HPP

#include "AudioPlayer.hpp"
#include "KeyboardInteraction.hpp"
#include "MusicLibrary.hpp"
#include "UserInterface.hpp"

class InterfaceController : public UserInterface, public KeyboardInteraction {
    UserInterface uiInstance;
    KeyboardInteraction kiInstance;
    AudioPlayer &apInstance;

  public:
    InterfaceController(
        UserInterface ui, KeyboardInteraction ki, AudioPlayer &ap)
        : uiInstance(ui), kiInstance(ki), apInstance(ap){};

    void createWindow(MusicLibrary &ml);

    static void entryPoint();

    void processKeyDown(MusicLibrary &ml, WIN_BOX &winBox, MENU_BOOL &menuBool);

    void moveOnScreen(
        MusicLibrary &ml, AudioPlayer &ap, WIN_BOX &winBox, int &input,
        MENU_BOOL &menuBool);
};
#endif // INTERFACECONTROLLER_HPP