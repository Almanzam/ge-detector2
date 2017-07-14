#filename=""
#while(filename==""){
#	filename <- readline(prompt="Enter File name: ")
#	if(is.na(filename)){break}
#}
args <- commandArgs()
data <- readLines(args[1],n=-1)

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
data2 <- as.numeric(data1)
#colnames(data2) <- "Energy (keV)"

file <- paste("hist",Sys.time(),".png",sep="")

png(filename=file)
hist(data2,breaks=1500,include.lowest=T)
dev.off()

