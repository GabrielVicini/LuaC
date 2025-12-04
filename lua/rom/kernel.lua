package.path = "lua/rom/?.lua;lua/rom/?/?.lua;" .. package.path

local text = require("rom.libraries.text")

local w, h = term.getSize()
local termLines = {}
local lineHeight = 8
local maxLines = math.floor(h / lineHeight)

local function getLineY(i)
    return (i - 1) * lineHeight
end

local function clearLine(i)
    local y = getLineY(i)
    term.fillRect(0, y, w, lineHeight, 0, 0, 0)
end

local function drawLine(i, line)
    local y = getLineY(i)
    text.drawText(0, y, line.text, line.r, line.g, line.b, 1)
end

local function termPrint(str, r, g, b)
    r = r or 255
    g = g or 255
    b = b or 255
    if not str then str = "Unknown!" end

    table.insert(termLines, {text = str, r = r, g = g, b = b})

    if #termLines > maxLines then
        table.remove(termLines, 1)
        term.scrollUp(lineHeight)
        drawLine(maxLines, termLines[#termLines])
    else
        local idx = #termLines
        clearLine(idx)
        drawLine(idx, termLines[idx])
    end
end

local function FPSCount()
    term.drawText(w - 50, h - 50, "Hello world!")
end

function main()
    while true do
        termPrint(tostring(sys.getUnixTime()))
        FPSCount()
        sys.wait(0.0001)
    end
end
