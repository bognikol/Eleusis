file(GLOB_RECURSE cpp_files_sample_app "./**/*.cpp")
file(GLOB_RECURSE h_files_sample_app "./**/*.h")

add_executable(sample_app "./main.cpp" "./SampleWindow.cpp" "./SampleWindow.h" ${cpp_files_sample_app} ${h_files_sample_app})
target_link_libraries(sample_app eleusis)
target_compile_options(sample_app PUBLIC "-std=c++11")

set_target_properties(sample_app PROPERTIES
  MACOSX_BUNDLE TRUE
  MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/Info.plist"
)

target_include_directories(sample_app PUBLIC "./")
target_include_directories(sample_app PUBLIC "./Views")

target_include_directories(sample_app PUBLIC "../Eleusis")
target_include_directories(sample_app PUBLIC "../Eleusis/00_eventing")
target_include_directories(sample_app PUBLIC "../Eleusis/01_os_backend")
target_include_directories(sample_app PUBLIC "../Eleusis/02_visual_parameters")
target_include_directories(sample_app PUBLIC "../Eleusis/03_noding")
target_include_directories(sample_app PUBLIC "../Eleusis/04_visual_primitives")
target_include_directories(sample_app PUBLIC "../Eleusis/04_visual_primitives/01_shapes")
target_include_directories(sample_app PUBLIC "../Eleusis/04_visual_primitives/02_text_block/01_text_block_impl")
target_include_directories(sample_app PUBLIC "../Eleusis/04_visual_primitives/02_text_block/02_select_edit")
target_include_directories(sample_app PUBLIC "../Eleusis/05_animation")
target_include_directories(sample_app PUBLIC "../Eleusis/07_controls/01_control_common")
target_include_directories(sample_app PUBLIC "../Eleusis/07_controls/02_control_impls")
target_include_directories(sample_app PUBLIC "../Eleusis/07_controls/02_control_impls/01_check_box")
target_include_directories(sample_app PUBLIC "../Eleusis/07_controls/02_control_impls/07_slider")
target_include_directories(sample_app PUBLIC "../Eleusis/08_utilities")
target_include_directories(sample_app PUBLIC "../Eleusis/08_utilities/01_to_string")
target_include_directories(sample_app PUBLIC "../Eleusis/08_utilities/02_pseudocontrols")

target_include_directories(sample_app PUBLIC "${GTK_ROOT}/include/cairo")
target_include_directories(sample_app PUBLIC "${GTK_ROOT}/include/pango-1.0")
target_include_directories(sample_app PUBLIC "${GTK_ROOT}/include/glib-2.0")
target_include_directories(sample_app PUBLIC "${GTK_ROOT}/lib/glib-2.0/include")
