CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )

if(COMMAND CMAKE_POLICY)
  cmake_policy(SET CMP0003 NEW)
endif()

PROJECT(RSA_preoperative_planner)


#---设置自动生成moc文件,不可缺少---------

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON) 

#----------------------------------------------------------------------------------
FIND_PACKAGE(VTK REQUIRED )
FIND_PACKAGE(ITK  REQUIRED)


INCLUDE( ${VTK_USE_FILE} )
INCLUDE(${ITK_USE_FILE})




#------------------------------------------
FIND_PACKAGE(Qt5Widgets)
FIND_PACKAGE(Qt5Core)
FIND_PACKAGE(Qt5Gui)
FIND_PACKAGE(Qt5OpenGL)
FIND_PACKAGE(Qt5Xml)

INCLUDE_DIRECTORIES(
${CMAKE_CURRENT_BINARY_DIR}
${CMAKE_CURRENT_SOURCE_DIR}
)

FILE(GLOB SRC_FILES "./*.cpp")
FILE(GLOB HEAD_FILES "./*.h")
FILE(GLOB UI_FILES "./*.ui")


SET(PROJECT_RESOURCE RSA_preoperative_planner.qrc)

#--------生成ui文件的头文件----------------
QT5_WRAP_UI(WRAP_FILES ${UI_FILES})
QT5_ADD_RESOURCES(PROJECT_RESOURCE_RCC ${PROJECT_RESOURCE})


ADD_EXECUTABLE(
               ${PROJECT_NAME}
               ${HEAD_FILES}
               ${SRC_FILES} 		   
               ${UI_FILES}
			   ${WRAP_FILES}
               ${WRAP_SRCS_H}
			   ${PROJECT_RESOURCE_RCC}
			   ${PROJECT_RESOURCE}
               )

TARGET_LINK_LIBRARIES(${PROJECT_NAME}
                      Qt5::Widgets
                      Qt5::Core
                      Qt5::Gui
                      Qt5::Xml
                      ${VTK_LIBRARIES}
                      ${ITK_LIBRARIES}) 

#---------添加筛选器----------------				  
source_group("Source Files" FILES ${SRC})
source_group("Header Files" FILES ${HDR})
source_group("Forms" FILES ${UI_FILES})
source_group("Forms\\WPAP_UI" FILES ${WRAP_FILES})

#source_group("Form Files" FILES ${UI})
#source_group("Resource Files" FILES ${RCC})
#source_group("Generate Files")




INCLUDE(CreateWindowsBatchScript.cmake)

IF(WIN32)
  SET(VS_SOLUTION_FILE "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.sln")
  FOREACH(VS_BUILD_TYPE debug release)
    CreateWindowsBatchScript("${CMAKE_SOURCE_DIR}/StartVS.bat.in"
      ${PROJECT_BINARY_DIR}/StartVS_${VS_BUILD_TYPE}.bat
      ${VS_BUILD_TYPE})
  ENDFOREACH()
ENDIF(WIN32)