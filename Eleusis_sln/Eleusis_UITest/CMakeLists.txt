file(GLOB_RECURSE cpp_files_ui_test "./**/*.cpp")
file(GLOB_RECURSE h_files_ui_test "./**/*.h")

add_executable(ui_test "./main.cpp" ${cpp_files_ui_test} ${h_files_ui_test})
target_link_libraries(ui_test eleusis)

set_target_properties(ui_test PROPERTIES
  WIN32_EXECUTABLE TRUE
  MACOSX_BUNDLE TRUE
  MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/Info.plist"
)

target_include_directories(ui_test PUBLIC "./")
target_include_directories(ui_test PUBLIC "./test_windows")
target_include_directories(ui_test PUBLIC "./test_windows/test_controls")
target_include_directories(ui_test PUBLIC "./test_windows/test_layout")

target_include_directories(ui_test PUBLIC "../Eleusis")
target_include_directories(ui_test PUBLIC "../Eleusis/00_eventing")
target_include_directories(ui_test PUBLIC "../Eleusis/01_os_backend")
target_include_directories(ui_test PUBLIC "../Eleusis/02_visual_parameters")
target_include_directories(ui_test PUBLIC "../Eleusis/03_noding")
target_include_directories(ui_test PUBLIC "../Eleusis/04_visual_primitives")
target_include_directories(ui_test PUBLIC "../Eleusis/04_visual_primitives/01_shapes")
target_include_directories(ui_test PUBLIC "../Eleusis/04_visual_primitives/02_text_block/01_text_block_impl")
target_include_directories(ui_test PUBLIC "../Eleusis/04_visual_primitives/02_text_block/02_select_edit")
target_include_directories(ui_test PUBLIC "../Eleusis/05_animation")
target_include_directories(ui_test PUBLIC "../Eleusis/07_controls/01_control_common")
target_include_directories(ui_test PUBLIC "../Eleusis/07_controls/02_control_impls")
target_include_directories(ui_test PUBLIC "../Eleusis/07_controls/02_control_impls/01_check_box")
target_include_directories(ui_test PUBLIC "../Eleusis/07_controls/02_control_impls/07_slider")
target_include_directories(ui_test PUBLIC "../Eleusis/08_utilities")
target_include_directories(ui_test PUBLIC "../Eleusis/08_utilities/01_to_string")
target_include_directories(ui_test PUBLIC "../Eleusis/08_utilities/02_pseudocontrols")

if (WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /GS /W3 /Gy /Zc:wchar_t /Zi /Gm- /fp:precise /errorReport:prompt /WX- /Zc:forScope /Gd /Oi /EHsc /nologo")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /GL /Zc:inline")
endif (WIN32)
