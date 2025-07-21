#!/bin/bash
for i in *.ppm; do
	magick "$i" "${i%.ppm}.png"
	rm "$i"
	optipng "${i%.ppm}.png" -strip all
done