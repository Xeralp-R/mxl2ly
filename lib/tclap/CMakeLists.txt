set (HEADERS
    Arg.h
    ArgContainer.h
    ArgException.h
    ArgGroup.h
    ArgTraits.h
    CmdLine.h
    CmdLineInterface.h
    CmdLineOutput.h
    Constraint.h
    DeferDelete.h
    DocBookOutput.h
    HelpVisitor.h
    IgnoreRestVisitor.h
    MultiArg.h
    MultiSwitchArg.h
    OptionalUnlabeledTracker.h
    sstream.h
    StandardTraits.h
    StdOutput.h
    UnlabeledMultiArg.h
    UnlabeledValueArg.h
    ValueArg.h
    ValuesConstraint.h
    VersionVisitor.h
    Visitor.h
)

#target_sources(TCLAP INTERFACE ${HEADER_FILES})
#install(FILES ${HEADER_FILES} DESTINATION include/tclap)

add_library(tclap INTERFACE
    ${HEADERS}
)

set_target_properties(tclap PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(tclap INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
