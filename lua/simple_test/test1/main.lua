-------------------------------------------------
-- LOVE: ParticleSystem demo.						
-- Website: http://love2d.org
-- Licence: ZLIB/libpng									
-- Copyright (c) 2006-2009 LOVE Development Team
-------------------------------------------------

systems = {}
current = 1

function love.load()
	cloud = love.graphics.newImage("cloud.png")
	x = 50
	y = 50
end

function love.draw()
	love.graphics.draw(cloud, x, y)
end

function love.update(dt)
	if love.keyboard.isDown("up") then
		y = y - 1000 * dt 
	elseif love.keyboard.isDown("down") then
		y = y + 1000 * dt
	elseif love.keyboard.isDown("right") then
		x = x + 1000 * dt 
	elseif love.keyboard.isDown("left") then
		x = x - 1000 * dt 
	end
end
