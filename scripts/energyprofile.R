data <- readLines("energies.txt",n=-1)

data1 <- gsub(pattern="Total energy deposited: ",
	      replacement="",
	      x=data)
data1 <- gsub(pattern="^G4WT[0-9] >",
              replacement="",
              x=data1)
data1 <- gsub(pattern=" eV",
	      replacement="e-03",
	      x=data1)
data1 <- gsub(pattern=" keV",
	      replacement="",
	      x=data1)
data1 <- gsub(pattern=" MeV",
              replacement="e3",
              x=data1)
data1 <- gsub(pattern="[[:space:]]",
              replacement="",
              x=data1)
data2 <- as.data.frame(as.numeric(data1))
colnames(data2) <- "Energy (keV)"

# png(filename="./hist.png")
# hist(data1)
# dev.off()
library(ggplot2)
hist<-ggplot(data2) +
    geom_histogram(aes(x=data2$`Energy (keV)`), stat="bin",binwidth = 1)

histlog<-ggplot(data2) +
    geom_histogram(aes(x=data2$`Energy (keV)`), stat="bin",binwidth = 1)+scale_y_log10()
file <- paste("hist",Sys.time(),".png",sep = "")
ggsave(hist,filename = file,device = "png")
