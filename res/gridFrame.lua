-- ************************************************************************** --
--                                                                            --
--                                                        :::      ::::::::   --
--   gridFrame.lua                                      :+:      :+:    :+:   --
--                                                    +:+ +:+         +:+     --
--   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        --
--                                                +#+#+#+#+#+   +#+           --
--   Created: 2016/03/02 19:57:41 by ngoguey           #+#    #+#             --
--   Updated: 2016/03/04 20:22:17 by ngoguey          ###   ########.fr       --
--                                                                            --
-- ************************************************************************** --

local INSETS = 5.; -- INSET BORDER OF THE VIEW
local SPACING = 1.; -- SPACING BETWEEN TILES

local FILL_COLOR = 0x0000FF + 0xC5000000
local BORDER_COLOR = 0x0000FF + 0xD0000000
local EMPTY_FILL_COLOR = FILL_COLOR - 0x45000000
local EMPTY_BORDER_COLOR = BORDER_COLOR - 0x25000000
local TEXT_COLOR = 0xFF555555

local f_w, f_wpx, f_main

local f_frame = gridFrame;
assert(f_frame ~= nil);

local function arrayLength(arr)
  if arr[0] == nil then
	return 0;
  else
	return #arr + 1;
  end
end

local function gridFontSize(w)
  return math.max(20 + 9 - w, 9);
end

local function drawTextCenter(canvas, text, x, y)
  local fontSize = gridFontSize(f_w);
  local text_w, text_h = canvas:measureText(text, fontSize);

  canvas:drawText(
	text, x - (text_w / 2), y - (text_h / 2), TEXT_COLOR, fontSize);
end

function f_frame:ON_BOARD_UPDATE()
  self:queryRedraw();
end

function f_frame:ON_BOARD_SIZE_UPDATE()
  f_w = Main:getBoardWidth();
  self:queryRedraw();
end

function f_frame:onDraw(canvas)
  if f_wpx == nil then
	f_w = Main:getBoardWidth();
	f_wpx, _ = f_frame:getSize();
  end

  local board = Main:getBoard()
  local status = Main:getGameStatus()

  local last = f_w - 1
  local tile_w = (f_wpx - INSETS * 2 - SPACING * last) / f_w

  local dt = tile_w + SPACING
  local ypx = INSETS
  local xpx = 0.
  local i = 0

  -- ft.ptab(board);
  assert(arrayLength(board) == f_w * f_w);

  for y = 0, last do
	xpx = INSETS;
	for x = 0, last do
	  i = y * f_w + x;
	  if board[i] >= 0 then
		canvas:drawRect(
		  xpx, ypx, xpx + tile_w, ypx + tile_w, FILL_COLOR, BORDER_COLOR, 8);
		drawTextCenter(
		  canvas, tostring(board[i]), xpx + (tile_w / 2), ypx + (tile_w / 2));
	  else
		canvas:drawRect(
		  xpx, ypx, xpx + tile_w, ypx + tile_w,
		  EMPTY_FILL_COLOR, EMPTY_BORDER_COLOR, 4);
	  end
	  xpx = xpx + dt;
	end
	ypx = ypx + dt;
  end

end

f_frame:setCallback('onDraw', f_frame.onDraw);
f_frame:registerEvent("ON_BOARD_UPDATE");
f_frame:registerEvent("ON_BOARD_SIZE_UPDATE");
