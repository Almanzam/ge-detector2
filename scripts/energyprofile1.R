#filename=""
#while(filename==""){
#	filename <- readline(prompt="Enter File name: ")
#	if(is.na(filename)){break}
#}
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

png(filename="./hist.png")
hist(data2$`Energy (keV)`,breaks=1500,include.lowest=T)
dev.off()

