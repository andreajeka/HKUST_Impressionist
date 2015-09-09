# Impressionist
#####You must add the following features to the Impressionist program:

1. [ ] Implement 5 different brush types: single line, scattered lines, scattered points, (filled) circles, and scattered (filled) circles. See the sample solution for an example of each brush's appearance. Note that scattered brushes should sample from each location they color individually, not just use a single color for each splotch. 
2. [ ] Add sliders to control various brush attributes. You need to include sliders for the line thickness and brush angle, in addition to the existing brush size slider. 
3. [ ] Add the ability to control the brush direction. The stroke direction should be controlled four different ways: using a slider value, using the right mouse button to drag out a direction line, using the direction of the cursor movement, and using directions that are perpendicular to the gradient of the image. You can use a radio box to allow the user to select which method to use. 
4. [ ] Allow the user to change the opacity (alpha value) of the brush stroke. An alpha value slider should be added to the controls window.

To see what these features should look like when they're done, you can look at the sample solution (with some of the extra credit) here. Your implementations of brush strokes, brush direction controls, etc. do not have to behave exactly the same as the sample solution, but they should be fairly close. Also, note that future updates to the sample solution will be available right here that display some of the bell and whistle implementations. 


#####Bells and Whistles (Extra features for extra points):
Here is a list of suggestions for extending the program. You are encouraged to come up with your own extensions. We're always interested in seeing new, unanticipated ways to use this program! 
  
1. [ ] ![whistle](http://i.imgur.com/VYSixYv.gif) To give your paintings more variety, add some additional brush types to the program. These brush strokes should be substantially different from those you are required to implement. You will get one whistle for each new brush (within reason). 

2. [ ] ![whistle](http://i.imgur.com/VYSixYv.gif) The skeleton program allows the user to paint outside the boundary of the paint rectangle, then erases this region when the stroke is completed. Change this to clip brush strokes to the region as they're being painted. 

3. [ ] ![whistle](http://i.imgur.com/VYSixYv.gif) When using your program, you currently can't see what part of the original image you're painting. Extend the program so that when the cursor is in the painting window, a marker appears on the original image showing where you're painting. 

4. [ ] ![whistle](http://i.imgur.com/VYSixYv.gif) Sometimes it is useful to use the contents of the painting window as the original image. Add a control to swap the contents of the painting window and the contents of the original image window. 

   1. [ ] ![bell](http://i.imgur.com/HJ7cCdM.gif) Add controls that allow you to manipulate the color of the image. For example, you could implement independent scaling of the red, green, and blue channels. 

     1. [ ] ![bell](http://i.imgur.com/HJ7cCdM.gif) Design a brush that selectively applies one or more filters such as blurring and sharpening. 

       1. [ ] ![bell](http://i.imgur.com/HJ7cCdM.gif) Add an undo feature with at least one level of undo so that you can try a brush and decide to undo its effect on the canvas. This comes in very handy for experimenting with brush and filtering effects. 

5. [ ] ![bell](http://i.imgur.com/HJ7cCdM.gif) Add the ability to dissolve one image into another. 

   1. [ ] ![bell+whistle](http://i.imgur.com/BxHJUfG.gif) A different solution to the problem of not being able to see where you're painting is to show a dimmed version of the painting on the canvas. Add a slider that allows the user to fade in or fade out the original image beneath the user's brush strokes on the canvas. (Beware, this bell and whistle is more difficult than it looks). 

6. [ ] ![bell+whistle](http://i.imgur.com/BxHJUfG.gif) Add a "mural" effect to your Impressionist by implementing the ability to load in different images while preserving what has been drawn on the canvas. Add a "New Mural Image" or "Change Mural Image" to the controls window that allows the user to change images. The user may then load an image, draw in what he / she prefers on the canvas, and then load a different image and continue drawing on the canvas; thus, a "mural" effect. 

7. [ ] ![bell+whistle](http://i.imgur.com/BxHJUfG.gif) To make your painting more interesting, add "alpha-mapped" brush strokes. In other words, allow the user to load a bitmap representing a brush stroke. This bitmap would contain an alpha value at each position. Then when this brush is used to draw, a single color would be selected from the image, all pixels in the brush bitmap would be set to this RGB color (without changing the alpha value), and this partially transparent bitmap would be painted on the canvas. A new color would be used each time the brush is drawn. 

8. [ ] ![bell+whistle](http://i.imgur.com/BxHJUfG.gif) It can be time-consuming to paint an image manually. Add a feature so that a whole painting can be created automatically. The user should only have to specify a brush type, size, and angle to use. Then the program should automatically paint brush strokes over the entire image, using a randomized brush order and varying the brush attributes slightly as it goes (to increase realism). 

9. [ ] ![bell+whistle](http://i.imgur.com/BxHJUfG.gif) At times, you may want the brush strokes to follow the gradient of a different image than the base image. Add a button(s) that will cause the direction of brush strokes to be automatically determined from a user specified image. 

10. [ ] ![bell+whistle](http://i.imgur.com/BxHJUfG.gif) The "accuracy" of the painting can be also be improved by clipping long brush strokes to edges in the image. Allow the user to load a black-and-white image that represents the edges in the picture. Then add a checkbox so that the user can turn on edge-clipping, which will automatically clip brush strokes at edges in the image. 

11. [ ] ![bell](http://i.imgur.com/HJ7cCdM.gif)![bell](http://i.imgur.com/HJ7cCdM.gif) Construct a filter kernel design interface so that you can enter the weights of filters of arbitrary sizes. Provide an "apply" button that will cause the convolution to happen. Include a "normalize" checkbox that will automatically divide by the sum of the weights when the user wishes it. 

12. [ ] ![bell](http://i.imgur.com/HJ7cCdM.gif)![bell](http://i.imgur.com/HJ7cCdM.gif) Use the image processing techniques described in class to automatically find the edges in the base image. Once you have found the edges, add a button to the user interface that will allow the user to select whether or not the brush strokes should be clipped to the edges in the picture. 

13. [ ] ![bell](http://i.imgur.com/HJ7cCdM.gif)![bell](http://i.imgur.com/HJ7cCdM.gif) Implement a multiresolution automatic painting technique. See [Painterly Styles for Expressive Rendering](http://mrl.nyu.edu/projects/npr/painterly/). 

   1. [ ] ![bell](http://i.imgur.com/HJ7cCdM.gif)![bell](http://i.imgur.com/HJ7cCdM.gif) Design a brush that can be used to stretch and pull the image as if it were rubber. See [Warp George Bush](http://mostfungames.com/warp-george-bush.htm). 

     1. [ ] ![bell](http://i.imgur.com/HJ7cCdM.gif)![bell](http://i.imgur.com/HJ7cCdM.gif) Implement a curved brush that follows the image gradient. [See Painterly Styles for Expressive Rendering](http://mrl.nyu.edu/projects/npr/painterly/). 
       1. [ ] ![bell](http://i.imgur.com/HJ7cCdM.gif)![bell](http://i.imgur.com/HJ7cCdM.gif)![bell](http://i.imgur.com/HJ7cCdM.gif)![bell](http://i.imgur.com/HJ7cCdM.gif) Given a source image, construct a new image that is really a mosaic of small (thumbnail) images. To do this, you need to partition the original into tiles and find new thumbnails that are reasonable matches to the tiles. Then draw the new image by substituting the thumbnails for the tiles. See, for example, Adam Finkelsteins [Web Gothic](http://www.cs.princeton.edu/~af/cool/webgothic.html). Credit will vary depending on the success of your method. 

14. [ ] ![bell](http://i.imgur.com/HJ7cCdM.gif)![bell](http://i.imgur.com/HJ7cCdM.gif)![bell](http://i.imgur.com/HJ7cCdM.gif)![bell](http://i.imgur.com/HJ7cCdM.gif) Extend the Impressionist program to work with video. The user should be able to load a series of images from a video and set up some initial parameters, and the program should automatically generate an impressionistic version of the video. The video should exhibit temporal coherency. 
 
15. [ ] ![bell](http://i.imgur.com/HJ7cCdM.gif)![bell](http://i.imgur.com/HJ7cCdM.gif)![bell](http://i.imgur.com/HJ7cCdM.gif)![bell](http://i.imgur.com/HJ7cCdM.gif)![bell](http://i.imgur.com/HJ7cCdM.gif) Implement [Bayesian matting](http://grail.cs.washington.edu/projects/digital-matting/image-matting/)

######Note: When downloading images from the sources above, remember to save them in BMP format!
