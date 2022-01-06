#pragma once

#ifndef _AD_BUILDCONFG_H_
#define _AD_BUILDCONFG_H_

#include <string>

namespace BuildConfig
{
    inline const std::string AssetsFolderPath  = ASSET_FOLDER_PATH;
    inline const std::string ShadersFolderPath = SHADER_FOLDER_PATH;
    inline const std::string MainFont = ASSET_FOLDER_PATH "Fonts/Fira_Sans/FiraSans-Regular.ttf";
}

#endif