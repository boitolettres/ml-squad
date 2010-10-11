project( squad )

cmake_minimum_required( VERSION 2.6 )

set( PACKAGE_NAME ${PROJECT_NAME} )
set( PACKAGE_VERSION 0.0.1 )
set( PACKAGE_RELEASE 0 )
set( PACKAGE_MAINTAINER_NAME "Dizan Vasquez" )
set( PACKAGE_MAINTAINER_EMAIL "dichodaemon@gmail.com" )
set( PACKAGE_DESCRIPTION_SUMMARY "Sequential Data library." )
set( PACKAGE_DESCRIPTION "Machine learning algorithms for sequential data." )
set( PACKAGE_DEPENDS )

include( SimpleCMake )
sm_configure_project()
