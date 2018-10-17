set(kdevqtdesigner_SRCS
    qtdesignerplugin.cpp
    qtdesignerdocument.cpp
    qtdesignerview.cpp
    qtdesignerwidget.cpp
)

ecm_qt_declare_logging_category(kdevqtdesigner_SRCS
    HEADER debug.h
    IDENTIFIER KDEVQTDESIGNER
    CATEGORY_NAME "kdevelop.plugins.qtdesigner"
)

kdevplatform_add_plugin(kdevqtdesigner
    JSON qtdesigner.json
    SOURCES ${kdevqtdesigner_SRCS}
)

target_link_libraries(kdevqtdesigner
    KDev::Interfaces
    KDev::Sublime
    Qt5::Designer
    # booooh, Qt developers forgot to give us cmake config files, did only pri ones
    # TODO: write some FindQt5DesignerComponents for now
    Qt5DesignerComponents
)
