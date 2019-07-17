file(GLOB_RECURSE cpp_files_unit_tests "./**/*.cpp")
file(GLOB_RECURSE h_files_unit_tests "./**/*.h")

add_executable(unit_tests "./main.cpp" "./gtest/src/gtest-all.cc" ${cpp_files_unit_tests} ${h_files_unit_tests})
target_link_libraries(unit_tests eleusis)

set_target_properties(unit_tests PROPERTIES
  MACOSX_BUNDLE FALSE
)

target_include_directories(unit_tests PUBLIC "./")
target_include_directories(unit_tests PUBLIC "./gtest/includes")
target_include_directories(unit_tests PUBLIC "./gtest")

target_include_directories(unit_tests PUBLIC "../Eleusis")
target_include_directories(unit_tests PUBLIC "../Eleusis/00_eventing")
target_include_directories(unit_tests PUBLIC "../Eleusis/01_os_backend")
target_include_directories(unit_tests PUBLIC "../Eleusis/02_visual_parameters")
target_include_directories(unit_tests PUBLIC "../Eleusis/03_noding")
target_include_directories(unit_tests PUBLIC "../Eleusis/04_visual_primitives")
target_include_directories(unit_tests PUBLIC "../Eleusis/04_visual_primitives/01_shapes")
target_include_directories(unit_tests PUBLIC "../Eleusis/04_visual_primitives/02_text_block/01_text_block_impl")
target_include_directories(unit_tests PUBLIC "../Eleusis/04_visual_primitives/02_text_block/02_select_edit")
target_include_directories(unit_tests PUBLIC "../Eleusis/05_animation")
target_include_directories(unit_tests PUBLIC "../Eleusis/07_controls/01_control_common")
target_include_directories(unit_tests PUBLIC "../Eleusis/07_controls/02_control_impls")
target_include_directories(unit_tests PUBLIC "../Eleusis/07_controls/02_control_impls/01_check_box")
target_include_directories(unit_tests PUBLIC "../Eleusis/07_controls/02_control_impls/07_slider")
target_include_directories(unit_tests PUBLIC "../Eleusis/08_utilities")
target_include_directories(unit_tests PUBLIC "../Eleusis/08_utilities/01_to_string")
target_include_directories(unit_tests PUBLIC "../Eleusis/08_utilities/02_pseudocontrols")

target_include_directories(unit_tests PUBLIC "${GTK_ROOT}/include/cairo")
target_include_directories(unit_tests PUBLIC "${GTK_ROOT}/include/pango-1.0")
target_include_directories(unit_tests PUBLIC "${GTK_ROOT}/include/glib-2.0")
target_include_directories(unit_tests PUBLIC "${GTK_ROOT}/lib/glib-2.0/include")