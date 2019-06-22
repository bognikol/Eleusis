
project(eleusis)


file(GLOB_RECURSE cpp_files "Eleusis/**/*.cpp")
file(GLOB_RECURSE f_files "Eleusis/**/*.h")
file(GLOB_RECURSE mm_files "Eleusis/**/*.mm")

add_library(eleusis SHARED ${cpp_files} ${h_files} ${mm_files})

target_compile_options(eleusis PUBLIC "-std=c++11")

target_include_directories(eleusis PUBLIC "Eleusis")
target_include_directories(eleusis PUBLIC "Eleusis/00_eventing")
target_include_directories(eleusis PUBLIC "Eleusis/01_os_backend")
target_include_directories(eleusis PUBLIC "Eleusis/02_visual_parameters")
target_include_directories(eleusis PUBLIC "Eleusis/03_noding")
target_include_directories(eleusis PUBLIC "Eleusis/04_visual_primitives")
target_include_directories(eleusis PUBLIC "Eleusis/04_visual_primitives/01_shapes")
target_include_directories(eleusis PUBLIC "Eleusis/04_visual_primitives/02_text_block/01_text_block_impl")
target_include_directories(eleusis PUBLIC "Eleusis/04_visual_primitives/02_text_block/01_select_edit")
target_include_directories(eleusis PUBLIC "Eleusis/05_animation")
target_include_directories(eleusis PUBLIC "Eleusis/07_controls/01_control_common")
target_include_directories(eleusis PUBLIC "Eleusis/08_utilities")


target_include_directories(eleusis PUBLIC "../Dependencies/02_macOS/40_gtk+/include/cairo")
target_include_directories(eleusis PUBLIC "../Dependencies/02_macOS/40_gtk+/include/pango-1.0")
target_include_directories(eleusis PUBLIC "../Dependencies/02_macOS/40_gtk+/include/glib-2.0")
target_include_directories(eleusis PUBLIC "../Dependencies/02_macOS/40_gtk+/lib/glib-2.0/include")

target_link_libraries(eleusis PUBLIC "/Users/bogdannikolic/Repositories/Eleusis/Dependencies/02_macOS/40_gtk+/lib/libcairo.dylib")
target_link_libraries(eleusis PUBLIC "/Users/bogdannikolic/Repositories/Eleusis/Dependencies/02_macOS/40_gtk+/lib/libpango-1.0.dylib")
target_link_libraries(eleusis PUBLIC "/Users/bogdannikolic/Repositories/Eleusis/Dependencies/02_macOS/40_gtk+/lib/libpangocairo-1.0.dylib")
target_link_libraries(eleusis PUBLIC "/Users/bogdannikolic/Repositories/Eleusis/Dependencies/02_macOS/40_gtk+/lib/libgobject-2.0.dylib")
find_library(COCOA_LIBRARY Cocoa)
target_link_libraries(eleusis PUBLIC ${COCOA_LIBRARY})


file(GLOB_RECURSE cpp_files_ui_test "Eleusis_UITest/**/*.cpp")
file(GLOB_RECURSE h_files_ui_test "Eleusis_UITest/**/*.h")

add_executable(ui_test "Eleusis_UITest/main.cpp" ${cpp_files_ui_test} ${h_files_ui_test})
target_link_libraries(ui_test eleusis)

target_compile_options(ui_test PUBLIC "-std=c++11")

target_include_directories(ui_test PUBLIC "Eleusis_UITest")
target_include_directories(ui_test PUBLIC "Eleusis_UITest/test_windows")
target_include_directories(ui_test PUBLIC "Eleusis_UITest/test_windows/test_controls")
target_include_directories(ui_test PUBLIC "Eleusis_UITest/test_windows/test_layout")

target_include_directories(ui_test PUBLIC "Eleusis")
target_include_directories(ui_test PUBLIC "Eleusis/00_eventing")
target_include_directories(ui_test PUBLIC "Eleusis/01_os_backend")
target_include_directories(ui_test PUBLIC "Eleusis/02_visual_parameters")
target_include_directories(ui_test PUBLIC "Eleusis/03_noding")
target_include_directories(ui_test PUBLIC "Eleusis/04_visual_primitives")
target_include_directories(ui_test PUBLIC "Eleusis/04_visual_primitives/01_shapes")
target_include_directories(ui_test PUBLIC "Eleusis/04_visual_primitives/02_text_block/01_text_block_impl")
target_include_directories(ui_test PUBLIC "Eleusis/04_visual_primitives/02_text_block/02_select_edit")
target_include_directories(ui_test PUBLIC "Eleusis/05_animation")
target_include_directories(ui_test PUBLIC "Eleusis/07_controls/01_control_common")
target_include_directories(ui_test PUBLIC "Eleusis/07_controls/02_control_impls")
target_include_directories(ui_test PUBLIC "Eleusis/07_controls/02_control_impls/01_check_box")
target_include_directories(ui_test PUBLIC "Eleusis/07_controls/02_control_impls/07_slider")
target_include_directories(ui_test PUBLIC "Eleusis/08_utilities")
target_include_directories(ui_test PUBLIC "Eleusis/08_utilities/01_to_string")
target_include_directories(ui_test PUBLIC "Eleusis/08_utilities/02_pseudocontrols")

target_include_directories(ui_test PUBLIC "../Dependencies/02_macOS/40_gtk+/include/cairo")
target_include_directories(ui_test PUBLIC "../Dependencies/02_macOS/40_gtk+/include/pango-1.0")
target_include_directories(ui_test PUBLIC "../Dependencies/02_macOS/40_gtk+/include/glib-2.0")
target_include_directories(ui_test PUBLIC "../Dependencies/02_macOS/40_gtk+/lib/glib-2.0/include")

