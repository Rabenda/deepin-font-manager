#ifndef GLOBALDEF_H
#define GLOBALDEF_H

#define DEFAULT_WINDOWS_WIDTH 820
#define DEFAULT_WINDOWS_HEIGHT 580

// Tool Search bar
#define FTM_TITLE_FIXED_HEIGHT 50
#define FTM_SEARCH_BAR_W 358
#define FTM_SEARCH_BAR_H 44

// Left navigation bar
#define FTM_LEFT_SIDE_BAR_WIDTH 145

// State bar
#define FTM_SBAR_HEIGHT 56

#define FTM_SBAR_TXT_EDIT_H 44
#define FTM_SBAR_TXT_EDIT_W 384  // Not used,Expanding now

#define FTM_SBAR_SLIDER_H 40
#define FTM_SBAR_SLIDER_W 199

#define FTM_SBAR_FSIZE_LABEL_H 40
#define FTM_SBAR_FSIZE_LABEL_W 32

// File manager binary name
#define DEEPIN_FILE_MANAGE_NAME "dde-file-manager"

// Left side bar debug test data
#define FTM_DEBUG_DATA_ON

// Uncomment follow line if need debug layout
//#define FTM_DEBUG_LAYOUT_COLOR

#define FTM_ENABLE_DISABLE_CACHE_DIR "/usr/local/.deep_fontmanger_cache"

#define FTM_REJECT_FONT_CONF_FILENAME  QString("71-DeepInFontManager-Reject.conf")

//Font Manager Theme Key
#define FTM_THEME_KEY "FontManagerTheme"

//Deepin manaul binary name
#define DEEPIN_MANUAL_NAME "dman"

//ToDo:
//Need to modify font manager binary name when dman is updated
//Font manager binary name
#define DEEPIN_FONT_MANAGER "deepin-font-installer"

#endif  // GLOBALDEF_H
