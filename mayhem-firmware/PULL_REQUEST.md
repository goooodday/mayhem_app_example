# feat: Add 'goooodday' sample application

## Description

This change introduces a new, simple internal application named "Gooood Day". The purpose of this app is to serve as a clear, working example for new developers, demonstrating how to create a basic view with text and button widgets.

The app displays the text "goooodday hyeongabshin" on the screen with a button to exit back to the main menu.

## Changes

- **Added `my_internal_app.hpp`**: Defines the `MyInternalAppView` class, including the `ui::Labels` widget for the text and a `Button` widget.
- **Added `my_internal_app.cpp`**: Implements the constructor and basic logic for the `MyInternalAppView`.

## How to Enable and Test

This pull request only adds the application source files. To complete the integration and see the app in the firmware, the following manual steps are required, as detailed in `02_INTERNAL_APP_DEVELOPMENT.md`:

1.  **Register the source file:** Add `apps/my_internal_app.cpp` to the `CPPSRC` list in `firmware/application/CMakeLists.txt`.
2.  **Add to menu:** Add the `MyInternalAppView` to the `appList` in `firmware/application/ui_navigation.cpp`.

After these steps, building and flashing the firmware will make the "Gooood Day" app available on the main menu.
