EventScript_FlyMenuError::
    msgbox sText_FlyMenuError, MSGBOX_SIGN
    waitmessage
    closemessage
    callnative ShowStartMenu
    waitstate
    end
sText_FlyMenuError:
    .string "Cannot travel from here.$"