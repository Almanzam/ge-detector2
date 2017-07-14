data <- scan("/raid5/almanzam/projects/ge-detector/build/energies.txt",quiet=T,what="character")

data1 <- gsub(pattern="Total energy deposited: ",
	      replacement="",
	      x=data)
data1 <- gsub(pattern=" eV",
	      replacement="",
	      x=data1)
data1 <- gsub(pattern=" keV",
	      replacement="*10^3",
	      x=data1)
data1 <- gsub(pattern="	MeV",
              replacement="*10^6",
              x=data1)
data1 <- as.numeric(data1)

png(filename="./hist.png")
hist(data1)
dev.off()
