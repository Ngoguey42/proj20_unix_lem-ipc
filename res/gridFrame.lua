-- ************************************************************************** --
--                                                                            --
--                                                        :::      ::::::::   --
--   gridFrame.lua                                      :+:      :+:    :+:   --
--                                                    +:+ +:+         +:+     --
--   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        --
--                                                +#+#+#+#+#+   +#+           --
--   Created: 2016/03/02 19:57:41 by ngoguey           #+#    #+#             --
--   Updated: 2016/03/04 19:22:07 by ngoguey          ###   ########.fr       --
--                                                                            --
-- ************************************************************************** --

local INSETS = 5.; -- INSET BORDER OF THE VIEW
local SPACING = 1.; -- SPACING BETWEEN TILES

local f_w, f_wpx, f_main

local f_frame = gridFrame;
assert(f_frame ~= nil);


-- local function getBoardWidth()
--   return 10;
-- end

local function gridFontSize(w)
  return math.max(20 + 9 - w, 9);
end

local function drawTextCenter(canvas, text, x, y)
  local fontSize = gridFontSize(f_w);
  local text_w, text_h = canvas:measureText(text, fontSize);

  canvas:drawText(text, x - (text_w / 2)
				  , y - (text_h / 2), 0xFF555555, fontSize);
end

function f_frame:ON_BOARD_UPDATE()
  self:queryRedraw();
end

function f_frame:onDraw(canvas)
  if f_wpx == nil then
	f_w = Main.getBoardWidth();
	f_wpx, _ = f_frame:getSize();
	-- f_main = Main:getMainInstance();
  end

  local board = Main.getBoard();
  ft.ptab(board); -- DEBUG

  local f_color = 0x0000FF + 0xA5000000
  local f_borderColor = 0x0000FF + 0xB0000000

  local last = f_w - 1;
  local tile_w = (f_wpx - INSETS * 2 - SPACING * last) / f_w;
  local realNbr;

  local dt = tile_w + SPACING;
  local ypx = INSETS;
  local xpx = 0.;
  local i = 0;


  for y = 0, last do
	xpx = INSETS;
	for x = 0, last do
	  i = y * f_w + x;
	  -- if realNbr ~= 0 then
		canvas:drawRect(xpx, ypx, xpx + tile_w, ypx + tile_w
						, f_color, f_borderColor, 8);
		drawTextCenter(canvas, tostring(42)
					   , xpx + (tile_w / 2), ypx + (tile_w / 2));
	  -- end
	  xpx = xpx + dt;
	end
	ypx = ypx + dt;
  end


end

f_frame:setCallback('onDraw', f_frame.onDraw);
f_frame:registerEvent("ON_BOARD_UPDATE");
