restaurant_recommendation
=========================

Utilize cgs_lda in topic_modeling toolkit in graphlab, and the ratings given by Yelp to find the similarity between the restaurants

This is a prototype for restaurant recommendation.

In this project, I firstly get the original files from the AllMenus API to get the menu information and the price information.
Then I get the corresponding files from Yelp API to get the ratings information.

After organizing the original files, I got the neat files with only the menus, price, and ratings. The ratings is computed by multiplying
the average rating for each restaurant with the number of ratings. Since a 3 star rated by 10 persons is different from a 3 star rated by
1000 persons. After getting the price for each dish, I computed the average price for each restaurant. Then I normalized both the ratings 
file and the price file. Then I computed the attribute similarity based on the price and ratings, using cosine similarity. This is one edge
between the restaurant nodes.

As to the menus, I used the cgs_lda method in the topic modeling toolkit, by GraphLab. I got the menus dictionary and the menus counts 
from the original file and make them be the input, then run it on the cluster. Then I got the output file, which includes the restaurant ID
and their corresponding topic distributions. Then I computed the similarity based on the topic distributions. This is another edge between 
the restaurant nodes.

With the two edges, I assign each of them be weighted 0.5. And built a general similarity metric for 100 restaurants.

The coefficients are still waiting to be updated. Since currently the only way to validate the data is to
visualize it and look at restaurants to see if the distances make sense. We are planning to farm it out as a Mechanical Turk task.
