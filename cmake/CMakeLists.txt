set(SOURCES
    main.cpp
)

set(THIS_IS_A_LIST
    -DEXPAT_RELATIVE_PATH
    -DFEATURE_ENABLE_VOICEMAIL
    -DGTEST_RELATIVE_PATH   # this is a comment, will be printed ?
    -DJSONCPP_RELATIVE_PATH
    -DLOGGING=1
)

message("THIS_IS_A_LIST with quotations :")        # no ""
message(${THIS_IS_A_LIST})
message("\n")
message("THIS_IS_A_LIST without quotations:")    # with ""
message("${THIS_IS_A_LIST}")
message("\n\n\n")

string(REPLACE ";" " " ThIS_IS_A_STRING "${THIS_IS_A_LIST}")
message("ThIS_IS_A_STRING with quotations:")         # no ""
message(${ThIS_IS_A_STRING})
message("\n")
message("ThIS_IS_A_STRING iwithout quotations:")   # with ""
message(${ThIS_IS_A_STRING})
message("\n\n\n")


