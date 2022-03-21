#############################
## SPEEEDUP AND EFFICIENCY ##
#############################
##   WEAK SCALABILITY      ##
#############################

library(tidyverse)
library(ggplot2)
#number of threads also called parallel workers
omp_n_threads = c(2, 4, 8, 12, 16, 20)
#parallel time for weak
omp_time = c(877.646, 819.649, 928.001, 903.205, 970.239, 861.964)
serial_time = 1177.77
Speedup <- c()
Efficiency <- c()

#appeding for the speedup
  for (time in omp_time){
    add_speedup <- serial_time/time #creating the value to add
    Speedup <- c(Speedup, add_speedup) #appending the new value to vector
  }

#appending for the efficiency
  for (eachSpeed in Speedup){
    for (thread in omp_n_threads){
    }#needed to iterate outside
    #after getting every speed and thread we iterate
    new_value <- eachSpeed /thread
    Efficiency <- c(Efficiency, new_value)
  }
df <- data.frame(omp_n_threads, omp_time,Speedup,Efficiency)

write.csv(df,"C:\\Users\\bruno\\Documents\\MEGAsync\\University\\1er trimestre\\2.foundations of HPC\\PROJECT2_BRUNO\\WeakScalability.csv")

theme_set(theme_bw())
ggplot(df, aes(x = omp_n_threads, y = omp_time)) +
  geom_line(color = "green", size = 1) +
  scale_x_continuous(trans = "log", breaks = c(2, 4, 8, 12, 16, 20)) +
  scale_y_continuous(limits = c(800,1000), breaks = seq(800, 1000, by = 20)) +
  labs(x = "number of processors",y = "Computational Time (s)") +
  theme(axis.text.y = element_text(vjust = 0, angle = 20, size = 15)) +
  theme(axis.text.x = element_text(vjust = 1, angle = 0, size = 15))

ggplot(df, aes(x = omp_n_threads, y = Speedup)) +
  geom_line(color = "red", size = 1) +
  scale_x_continuous(trans = "log", breaks = c( 2, 4, 8,12, 16, 20)) +
  scale_y_continuous(limits = c(1.2, 1.5), breaks = seq(1.2, 1.5, by = 0.02)) +
  labs(x = "number of processors",y = "Speedup") +
  theme(axis.text.y = element_text(vjust = 0, angle = 20, size = 15)) +
  theme(axis.text.x = element_text(vjust = 1, angle = 0, size = 15))

ggplot(df, aes(x = omp_n_threads, y = Efficiency)) +
  geom_line(color = "blue", size = 1) +
  scale_x_continuous(trans = "log", breaks = c( 2, 4, 8,12, 16, 20)) +
  scale_y_continuous(limits = c(0.060,0.080), breaks = seq(0.060,0.080, by = 0.002)) +
  labs(x = "number of processors",y = "Effeciency") +
  theme(axis.text.y = element_text(vjust = 0, angle = 20, size = 15)) +
  theme(axis.text.x = element_text(vjust = 1, angle = 0, size = 15))

########################
## STRONG SCALABILITY ##
########################
#number of threads also called parallel workers
omp_n_threads_s = c(1, 2, 4, 8, 16, 32)
#parallel time for weak
omp_time_s = c(1597.81, 446.742, 190.362, 108.818, 38.8168, 17.2733)
serial_time_s = 1177.77
Speedup_s <- c()
Efficiency_s <- c()

#appeding for the speedup
for (time_s in omp_time_s){
  add_speedup_s <- serial_time_s/time_s #creating the value to add
  Speedup_s <- c(Speedup_s, add_speedup_s) #appending the new value to vector
}

#appending for the efficiency
for (eachSpeed_s in Speedup_s){
  for (thread_s in omp_n_threads_s){
  }#needed to iterate outside
  #after getting every speed and thread we iterate
  new_value_s <- eachSpeed_s /thread_s
  Efficiency_s <- c(Efficiency_s, new_value_s)
}

df2 <- data.frame(omp_n_threads_s, omp_time_s, Speedup_s, Efficiency_s)

write.csv(df,"C:\\Users\\bruno\\Documents\\MEGAsync\\University\\1er trimestre\\2.foundations of HPC\\PROJECT2_BRUNO\\WeakScalability.csv")

theme_set(theme_bw())
ggplot(df2, aes(x = omp_n_threads_s, y = omp_time_s)) +
  geom_line(color = "green", size = 1) +
  scale_x_continuous(trans = "log", breaks = c(1, 2, 4, 8, 16, 32)) +
  scale_y_continuous(limits = c(15,1600), breaks = seq(15, 1600, by = 100)) +
  labs(x = "number of processors",y = "Computational Time (s)") +
  theme(axis.text.y = element_text(vjust = 0, angle = 20, size = 15)) +
  theme(axis.text.x = element_text(vjust = 1, angle = 0, size = 15))

ggplot(df2, aes(x = omp_n_threads_s, y = Speedup_s)) +
  geom_line(color = "red", size = 1) +
  scale_x_continuous(trans = "log", breaks = c(1, 2, 4, 8, 16, 32)) +
  scale_y_continuous(limits = c(0.73, 70), breaks = seq(0.73, 70, by = 5)) +
  labs(x = "number of processors",y = "Speedup") +
  theme(axis.text.y = element_text(vjust = 0, angle = 20, size = 15)) +
  theme(axis.text.x = element_text(vjust = 1, angle = 0, size = 15))

ggplot(df2, aes(x = omp_n_threads_s, y = Efficiency_s)) +
  geom_line(color = "blue", size = 1) +
  scale_x_continuous(trans = "log", breaks = c(1, 2, 4, 8, 16, 32)) +
  scale_y_continuous(limits = c(0.020,2.20), breaks = seq(0.020,2.20, by = 0.2)) +
  labs(x = "number of processors",y = "Effeciency") +
  theme(axis.text.y = element_text(vjust = 0, angle = 20, size = 15)) +
  theme(axis.text.x = element_text(vjust = 1, angle = 0, size = 15))



