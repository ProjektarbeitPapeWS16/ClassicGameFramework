#pragma once
#include "Position.h"

// Boundaries in pixels, for the level or entities
struct Boundaries
{
	Position position;
	int width, height, off_left, off_right, off_top, off_bottom;
	/**
	 * Creates boundaries for anything.
	 * 
	 * @param x Starting position on x axis
	 * @param y Starting position on y axis
	 * @param width Width
	 * @param height Height
	 */
	Boundaries(int x, int y, int width, int height);

	/**
	 * Creates boundaries with offsets for anything, using {@link Boundaries(int x, int y, int width, int height)}.
	 * 
	 * @param x Starting position on x axis
	 * @param y Starting position on y axis
	 * @param width Width
	 * @param height Height
	 * @param off_left Left Offset
	 * @param off_bottom Bottom Offset
	 * @param off_right Right Offset
	 * @param off_top Top Offset
	 */
	Boundaries(int x, int y, int width, int height, int off_left, int off_bottom, int off_right, int off_top);

	/**
	 * @returns The position on the x-axis in consideration of the offset.
	 */
	int real_x() const;
	
	/**
	* @returns The position on the y-axis in consideration of the offset.
	*/
	int real_y() const;
	
	/**
	* @returns The width in consideration of the offset.
	*/
	int real_width() const;
	
	/**
	* @returns The height in consideration of the offset.
	*/
	int real_height() const;
};
