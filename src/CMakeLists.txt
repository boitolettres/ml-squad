#-------------------------------------------------------------------------------
# Library
#-------------------------------------------------------------------------------

#~ add_library( <LIBRARY_NAME> SHARED <SOURCE_LIST> )
#~ 
#~ add_executable( <EXECUTABLE_NAME> <SOURCE_LIST> )
#~ target_link_libraries( <TARGET_NAME> <LINKED_LIBRARY> )
#~ 
#~ sm_cpp_install( <TARGET_LIST> )

sm_cpp_install_headers( squad )

#-------------------------------------------------------------------------------
# Sandbox
#-------------------------------------------------------------------------------

include_directories( /usr/include/eigen2 )

add_executable( testKMeans sandbox/testKMeans.cpp )
target_link_libraries( testKMeans sfml-window sfml-graphics )
