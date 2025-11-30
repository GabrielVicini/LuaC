local width  = 620
local height = 360

local backspace_down = false
local backspace_timer = 0
local BACKSPACE_DELAY = 90
local BACKSPACE_REPEAT = 2

local input = ""
local mouseDebug = false

local pointer = {
"X.....",
"XX....",
"X.X...",
"X..X..",
"X...X.",
"X....X",
"X.....X",
"XX....X",
".XX...X",
"..XXXX."
}

local font = {
    [" "]={"     ","     ","     ","     ","     ","     ","     "},
    ["!"]={"  X  ","  X  ","  X  ","  X  ","     ","     ","  X  "},
    ["\""]={" X X "," X X ","     ","     ","     ","     ","     "},
    ["#"]={" X X ","XXXXX"," X X ","XXXXX"," X X ","     ","     "},
    ["$"]={" XXX ","X X  "," XXX ","  X X"," XXX ","  X  ","     "},
    ["%"]={"X   X","   X ","  X  "," X   ","X   X","     ","     "},
    ["&"]={" XX  ","X  X "," XX  ","X  X "," XX X","     ","     "},
    ["'"]={"  X  ","  X  ","     ","     ","     ","     ","     "},
    ["("]={"   X ","  X  "," X   "," X   ","  X  ","   X ","     "},
    [")"]={" X   ","  X  ","   X ","   X ","  X  "," X   ","     "},
    ["*"]={"     "," X X ","XXXXX"," X X ","     ","     ","     "},
    ["+"]={"     ","  X  "," XXX ","  X  ","     ","     ","     "},
    [","]={"     ","     ","     ","     ","  X  ","  X  "," X   "},
    ["-"]={"     ","     "," XXX ","     ","     ","     ","     "},
    ["."]={"     ","     ","     ","     ","     ","  X  ","  X  "},
    ["/"]={"    X","   X ","  X  "," X   ","X    ","     ","     "},

    ["0"]={" XXX ","X   X","X  XX","X X X","XX  X","X   X"," XXX "},
    ["1"]={"  X  "," XX  ","  X  ","  X  ","  X  ","  X  "," XXX "},
    ["2"]={" XXX ","X   X","    X","   X ","  X  "," X   ","XXXXX"},
    ["3"]={"XXXXX","    X","   X ","    X","    X","X   X"," XXX "},
    ["4"]={"   X ","  XX "," X X ","X  X ","XXXXX","   X ","   X "},
    ["5"]={"XXXXX","X    ","XXXX ","    X","    X","X   X"," XXX "},
    ["6"]={"  XX "," X   ","X    ","XXXX ","X   X","X   X"," XXX "},
    ["7"]={"XXXXX","    X","   X ","  X  ","  X  ","  X  ","  X  "},
    ["8"]={" XXX ","X   X","X   X"," XXX ","X   X","X   X"," XXX "},
    ["9"]={" XXX ","X   X","X   X"," XXXX","    X","   X "," XX  "},

    [":"]={"     ","  X  ","     ","     ","  X  ","     ","     "},
    [";"]={"     ","  X  ","     ","     ","  X  ","  X  "," X   "},
    ["<"]={"   X ","  X  "," X   ","  X  ","   X ","     ","     "},
    ["="]={"     "," XXX ","     "," XXX ","     ","     ","     "},
    [">"]={" X   ","  X  ","   X ","  X  "," X   ","     ","     "},
    ["?"]={" XXX ","X   X","    X","   X ","  X  ","     ","  X  "},

    ["@"]={" XXX ","X   X","X XXX","X X X","X XXX","X    "," XXX "},

    ["A"]={" XXX ","X   X","X   X","XXXXX","X   X","X   X","X   X"},
    ["B"]={"XXXX ","X   X","X   X","XXXX ","X   X","X   X","XXXX "},
    ["C"]={" XXX ","X   X","X    ","X    ","X    ","X   X"," XXX "},
    ["D"]={"XXXX ","X   X","X   X","X   X","X   X","X   X","XXXX "},
    ["E"]={"XXXXX","X    ","X    ","XXXX ","X    ","X    ","XXXXX"},
    ["F"]={"XXXXX","X    ","X    ","XXXX ","X    ","X    ","X    "},
    ["G"]={" XXX ","X   X","X    ","X XXX","X   X","X   X"," XXX "},
    ["H"]={"X   X","X   X","X   X","XXXXX","X   X","X   X","X   X"},
    ["I"]={" XXX ","  X  ","  X  ","  X  ","  X  ","  X  "," XXX "},
    ["J"]={"XXXXX","    X","    X","    X","    X","X   X"," XXX "},
    ["K"]={"X   X","X  X ","X X  ","XX   ","X X  ","X  X ","X   X"},
    ["L"]={"X    ","X    ","X    ","X    ","X    ","X    ","XXXXX"},
    ["M"]={"X   X","XX XX","X X X","X   X","X   X","X   X","X   X"},
    ["N"]={"X   X","XX  X","X X X","X  XX","X   X","X   X","X   X"},
    ["O"]={" XXX ","X   X","X   X","X   X","X   X","X   X"," XXX "},
    ["P"]={"XXXX ","X   X","X   X","XXXX ","X    ","X    ","X    "},
    ["Q"]={" XXX ","X   X","X   X","X   X","X X X","X  X "," XX X"},
    ["R"]={"XXXX ","X   X","X   X","XXXX ","X X  ","X  X ","X   X"},
    ["S"]={" XXX ","X   X","X    "," XXX ","    X","X   X"," XXX "},
    ["T"]={"XXXXX","  X  ","  X  ","  X  ","  X  ","  X  ","  X  "},
    ["U"]={"X   X","X   X","X   X","X   X","X   X","X   X"," XXX "},
    ["V"]={"X   X","X   X","X   X","X   X","X   X"," X X ","  X  "},
    ["W"]={"X   X","X   X","X   X","X X X","X X X","XX XX","X   X"},
    ["X"]={"X   X"," X X ","  X  ","  X  ","  X  "," X X ","X   X"},
    ["Y"]={"X   X"," X X ","  X  ","  X  ","  X  ","  X  ","  X  "},
    ["Z"]={"XXXXX","    X","   X ","  X  "," X   ","X    ","XXXXX"},

    ["["]={" XXX "," X   "," X   "," X   "," X   "," X   "," XXX "},
    ["\\"]={"X    "," X   ","  X  ","   X ","    X","     ","     "},
    ["]"]={" XXX ","   X ","   X ","   X ","   X ","   X "," XXX "},
    ["^"]={"  X  "," X X ","     ","     ","     ","     ","     "},
    ["_"]={"     ","     ","     ","     ","     ","     ","XXXXX"},

    ["`"]={" X   ","  X  ","     ","     ","     ","     ","     "},

    ["a"]={"     "," XXX ","    X"," XXXX","X   X","X   X"," XXXX"},
    ["b"]={"X    ","X    ","XXXX ","X   X","X   X","X   X","XXXX "},
    ["c"]={"     "," XXX ","X   X","X    ","X    ","X   X"," XXX "},
    ["d"]={"    X","    X"," XXXX","X   X","X   X","X   X"," XXXX"},
    ["e"]={"     "," XXX ","X   X","XXXXX","X    ","X   X"," XXX "},
    ["f"]={"  XX "," X  X"," X   ","XXX  "," X   "," X   "," X   "},
    ["g"]={"     "," XXXX","X   X","X   X"," XXXX","    X"," XXX "},
    ["h"]={"X    ","X    ","XXXX ","X   X","X   X","X   X","X   X"},
    ["i"]={"  X  ","     "," XX  ","  X  ","  X  ","  X  "," XXX "},
    ["j"]={"   X ","     ","  XX ","   X ","   X ","   X "," XX  "},
    ["k"]={"X    ","X   X","X  X ","XXX  ","X  X ","X   X","X   X"},
    ["l"]={" XX  ","  X  ","  X  ","  X  ","  X  ","  X  "," XXX "},
    ["m"]={"     ","XXXX ","X X X","X X X","X   X","X   X","X   X"},
    ["n"]={"     ","XXXX ","X   X","X   X","X   X","X   X","X   X"},
    ["o"]={"     "," XXX ","X   X","X   X","X   X","X   X"," XXX "},
    ["p"]={"     ","XXXX ","X   X","X   X","XXXX ","X    ","X    "},
    ["q"]={"     "," XXXX","X   X","X   X"," XXXX","    X","    X"},
    ["r"]={"     "," XXX ","X   X","X    ","X    ","X    ","X    "},
    ["s"]={"     "," XXXX","X    "," XXX ","    X","X   X"," XXX "},
    ["t"]={"     ","  X  "," XXX ","  X  ","  X  ","  X  ","  XX "},
    ["u"]={"     ","X   X","X   X","X   X","X   X","X   X"," XXXX"},
    ["v"]={"     ","X   X","X   X","X   X","X   X"," X X ","  X  "},
    ["w"]={"     ","X   X","X   X","X X X","X X X","XX XX","X   X"},
    ["x"]={"     ","X   X"," X X ","  X  ","  X  "," X X ","X   X"},
    ["y"]={"     ","X   X","X   X","X   X"," XXXX","    X"," XXX "},
    ["z"]={"     ","XXXXX","   X ","  X  "," X   ","X    ","XXXXX"},

    ["{"]={"   X ","  X  ","  X  "," X   ","  X  ","  X  ","   X "},
    ["|"]={"  X  ","  X  ","  X  ","     ","  X  ","  X  ","  X  "},
    ["}"]={" X   ","  X  ","  X  ","   X ","  X  ","  X  "," X   "},
    ["~"]={"     "," X X ","X X X","     ","     ","     ","     "}
}

local function draw_char(char, px, py, r, g, b)
    local glyph = font[char]
    if not glyph then return end

    for y = 1, 7 do
        local row = glyph[y]
        for x = 1, 5 do
            if row:sub(x, x) == "X" then
                screen.setPixel(px + x, py + y, r, g, b)
            end
        end
    end
end

local function draw_text(str, px, py, r, g, b)
    local x = px
    for i = 1, #str do
        local ch = str:sub(i, i)
        draw_char(ch, x, py, r, g, b)
        x = x + 6
    end
end


local cursor_timer = 0
local cursor_state = true
local lines = {}
local MAX_LINES = 25

local mouse_x, mouse_y = 0, 0
local last_mouse_x, last_mouse_y = 0, 0

local mouse_prev = {
    left   = false,
    right  = false,
    middle = false
}

local function print_line(text)
    table.insert(lines, text)
    if #lines > MAX_LINES then
        lines = {}
    end
end

local cube_active = false
local cube_angle = 0

local cube_vertices = {
    {-1,-1,-1}, {1,-1,-1}, {1,1,-1}, {-1,1,-1},
    {-1,-1, 1}, {1,-1, 1}, {1,1, 1}, {-1,1, 1},
}

local cube_edges = {
    {1,2},{2,3},{3,4},{4,1},
    {5,6},{6,7},{7,8},{8,5},
    {1,5},{2,6},{3,7},{4,8},
}

local function rotateY(x,y,z,a)
    local ca, sa = math.cos(a), math.sin(a)
    return x*ca - z*sa, y, x*sa + z*ca
end

local function rotateX(x,y,z,a)
    local ca, sa = math.cos(a), math.sin(a)
    return x, y*ca - z*sa, y*sa + z*ca
end

local function project(x,y,z)
    local f = 200 / (z + 4)
    return x*f + width/2, y*f + height/2
end

function draw_cube()
    local pts = {}

    for i,v in ipairs(cube_vertices) do
        local x,y,z = v[1],v[2],v[3]

        x,y,z = rotateY(x,y,z,cube_angle)
        x,y,z = rotateX(x,y,z,cube_angle*0.7)

        local sx, sy = project(x,y,z)
        pts[i] = {sx, sy}
    end

    for _,e in ipairs(cube_edges) do
        local a = pts[e[1]]
        local b = pts[e[2]]
        draw_line(a[1],a[2], b[1],b[2], 0, 255, 255)
    end
end

function draw_line(x0, y0, x1, y1, r, g, b)
    x0 = math.floor(x0)
    y0 = math.floor(y0)
    x1 = math.floor(x1)
    y1 = math.floor(y1)

    local dx = math.abs(x1 - x0)
    local dy = -math.abs(y1 - y0)
    local sx = x0 < x1 and 1 or -1
    local sy = y0 < y1 and 1 or -1
    local err = dx + dy

    while true do
        if x0 >= 0 and y0 >= 0 and x0 < width and y0 < height then
            screen.setPixel(x0, y0, r, g, b)
        end

        if x0 == x1 and y0 == y1 then break end
        local e2 = 2 * err
        if e2 >= dy then err = err + dy; x0 = x0 + sx end
        if e2 <= dx then err = err + dx; y0 = y0 + sy end
    end
end


local function run_command(cmd)
    if cmd == "help" then
        print_line("Available commands:")
        print_line(" help - show this help message")
        print_line(" cls  - clear the screen")
        print_line(" echo <text> - repeat text")
        print_line(" mouse - toggle mouse debug")
        print_line(" cube - press enter to exit :)")
        return
    end

    if cmd == "cube" then
        cube_active = true
        cursor_state = true
        return
    end


    if cmd == "cls" then
        lines = {}
        return
    end

    if cmd == "mouse" then
        mouseDebug = not mouseDebug
        print_line("Mouse debug is now: "..tostring(mouseDebug))
        return
    end

    if cmd:sub(1, 5) == "echo " then
        print_line(cmd:sub(6))
        return
    end

    print_line("Unknown command: " .. cmd)
end

local function draw_pointer(px, py, r, g, b)
    for y = 1, #pointer do
        local row = pointer[y]
        for x = 1, #row do
            if row:sub(x,x) == "X" then
                screen.setPixel(px + x - 1, py + y - 1, r, g, b)
            end
        end
    end
end

local function redraw_screen()
    screen.clear()

    draw_text("Default Kernal V1.0", 10, 10, 0, 235, 0)
    draw_text('Welcome! Type "Help" if you need help!', 10, 30, 255, 255, 255)

    local y = 45
    for _, line in ipairs(lines) do
        draw_text(line, 10, y, 255, 255, 255)
        y = y + 12
    end

    draw_text("$ " .. input, 10, y, 0, 235, 0)

    if cursor_state then
        local cursor_x = 10 + (#("$ " .. input) * 6)
        local cursor_y = y + 8
        for px = 0, 4 do
            screen.setPixel(cursor_x + px, cursor_y, 0, 235, 0)
        end
    end

    if mouse_x >= 0 and mouse_y >= 0 and mouse_x < width and mouse_y < height then
        draw_pointer(mouse_x, mouse_y, 0, 200, 255)
    end
end

function OnKeyPress(ch)
    if ch == "\b" then
        input = input:sub(1, -2)
        backspace_down = true
        backspace_timer = 0
        return
    end

    if ch == "\n" then
        if cube_active then
            cube_active = false
            input = ""
            return
        else
            if #input > 0 then
                run_command(input)
            end
            input = ""
            return
           end
    end

    if #ch == 1 then
        input = input .. ch
    end
end

function OnFrame()
    if cube_active then
        cube_angle = cube_angle + 0.03
        screen.clear()
        draw_cube()
        return
    end

    cursor_timer = cursor_timer + 1
    if cursor_timer > 30 then
        cursor_timer = 0
        cursor_state = not cursor_state
    end

    redraw_screen()
end


function OnMouseMove(x, y)
    mouse_x, mouse_y = x, y
end

function OnMouseButton(button, action, x, y)
    if action == "down" then
        print_line(string.format("Mouse %s down @ %d,%d", button, x, y))
    end
end

function OnMouseWheel(delta, x, y)
    print_line(string.format("Wheel %+0.2f @ %d,%d", delta, x, y))
end


function update()

    local ch = system.keyboard.getChar()
    if ch and type(ch) == "string" and #ch > 0 then
        if OnKeyPress then
            OnKeyPress(ch)
        end
    end

if backspace_down then
    backspace_timer = backspace_timer + 1

    if not system.keyboard.isDown(system.keyboard.KEY_BACKSPACE) then
        backspace_down = false
        backspace_timer = 0
    else

        if backspace_timer > BACKSPACE_DELAY then
            if backspace_timer % BACKSPACE_REPEAT == 0 then
                input = input:sub(1, -2)
            end
        end
    end
end


    system.mouse.hide()

    local mx, my = system.mouse.getPosition()
    if mx ~= last_mouse_x or my ~= last_mouse_y then
        last_mouse_x, last_mouse_y = mx, my
        if OnMouseMove then
            OnMouseMove(mx, my)
        end
    end


    local function handleButton(fieldName, luaName, buttonConst)
        local down = system.mouse.isDown(buttonConst)
        local prev = mouse_prev[fieldName]
        if down ~= prev then
            mouse_prev[fieldName] = down
            if OnMouseButton then
                local action = down and "down" or "up"
                OnMouseButton(luaName, action, mx, my)
            end
        end
    end

    if mouseDebug then
        handleButton("left",   "left",   system.mouse.BUTTON_LEFT)
        handleButton("right",  "right",  system.mouse.BUTTON_RIGHT)
        handleButton("middle", "middle", system.mouse.BUTTON_MIDDLE)
    end

    local wheel = system.mouse.getWheelMove()
    if wheel ~= 0 and OnMouseWheel then
        if mouseDebug then
            OnMouseWheel(wheel, mx, my)
        end
    end

    if OnFrame then
        OnFrame()
    end
end