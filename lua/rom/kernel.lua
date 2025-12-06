package.path = "lua/rom/?.lua;lua/rom/?/?.lua;" .. package.path

local w, h = term.getSize()
local text = require("libraries.text")

function main()
    text.drawText(20, 20, "Hello world!", 0)
end