cmake_minimum_required(VERSION 3.0)

project(kdevqtdesigner)

find_package(ECM "5.14.0" REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMQtDeclareLoggingCategory)
include(FeatureSummary)

find_package(Qt5 5.5.0 CONFIG REQUIRED Core Gui Widgets Designer)

find_package(KDevPlatform 5.2.80 REQUIRED)

add_subdirectory(src)

# kdebugsettings file
install(FILES kdevqtdesigner.categories DESTINATION ${KDE_INSTALL_CONFDIR})

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
