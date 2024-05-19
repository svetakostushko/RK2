include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_CONTACT XXX@gmail.com)
set(CPACK_PACKAGE_VERSION ${PRINT_VERSION})
set(CPACK_PACKAGE_NAME "game")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "RK2")
set(CPACK_PACKAGE_VENDOR "v1pzer")
set(CPACK_PACKAGE_PACK_NAME "example-${PRINT_VERSION}")

set(CPACK_SOURCE_INSTALLED_DIRECTORIES 
	"${CMAKE_SOURCE_DIR}/example_application; example_application"
	"${CMAKE_SOURCE_DIR}/tests; tests")

set(CPACK_SOURCE_GENERATOR "TGZ;ZIP")

set(CPACK_DEBIAN_PACKAGE_VERSION ${PRINT_VERSION})
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "all")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "game")

set(CPACK_GENERATOR "DEB;RPM")

set(CPACK_RPM_PACKAGE_SUMMARY "game")

include(CPack)
