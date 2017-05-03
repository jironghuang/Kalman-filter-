#Note: Trying to replicate the results in Kalman filter assignment using R. Create the protoype today. Then figure out syntax and oop part in C++

library("mnormt")

##################################################
#Create the main script (loop 50 times)

#read.csv
k = read.csv("C:/Users/Huang Jirong/Desktop/kal_obs.csv")

for(i in 1:50){
#Prediction
F = matrix(c(1, 0, 0,
             0, 1, 1,
             0, 0, 1), ncol = 3 ,nrow=3)
F = t(F)

if(i == 1){
xhatf = c(38000, 0, 0)      #expected position at time 0. Represents the x and y axis respectively. Hw can feed in the 38k, 0 and 0  
}else{}

xhatf = as.matrix(xhatf)

#Prediction part 1-->correct!
xhat = F %*% xhatf

if(i == 1){
  sigmaf = matrix(c(100000, 0, 0,
                    0, 100000,0,
                    0, 0, 100000), ncol=3)     #Position follows a normal distribution with covariance matrix. Hw feed in 3*3 matrix of var-cov matrix
}else{}


Q = matrix(c(500^2, 0, 0,
             0, 0.005^2, 0,
             0, 0, 0.005^2), ncol=3)     #Position follows a normal distribution with covariance matrix. Hw feed in 3*3 matrix of var-cov matrix


sigma = F %*% sigmaf %*% t(F) + Q

#Prediction part 2
H = diag(3); H = H[-3,]      #Somewhat like identity matrix (but 9th position is 0). This is related to the sensor model
#Sensor information
#Observation noise matrix-->Look at the 2000 and 0.03 instead 
R = matrix(c(2000^2,0,
             0, 0.03^2
),nrow = 2, ncol=2)     #Position follows a normal distribution with covariance matrix. Hw feed in 3*3 matrix of var-cov matrix

Kalman_gain = sigma %*% t(H) %*% solve(H %*% sigma %*% t(H) + R)

z = as.matrix(c(k[i,1], k[i,2]))     #This should be read in from external source

# xhatf <- xhat + Kalman_gain %*% (y - H %*% xhat)     #Part of equation is Kalman gain
xhatf = xhat + Kalman_gain %*% (z - H %*% xhat)     #Part of equation is Kalman gain
sigmaf = sigma - Kalman_gain %*% H %*% sigma        #Get variance 1-9 correct

}

