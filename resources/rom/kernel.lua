package.path = "lua/rom/?.lua;lua/rom/?/?.lua;" .. package.path

local w, h = term.getSize()
local text = require("libraries.text")

function main()
    text.drawText(20, 20, "RetroC", 255, 255, 255, 3)
    text.drawText(20, 60, "Hello world!", 255, 255, 255, 3)
end
