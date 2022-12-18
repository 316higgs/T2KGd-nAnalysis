include $(SKOFL_ROOT)/config.gmk

LOCAL_LIBS += -L$(ANAT2KSK_ROOT)/lib -lcc0pinumu
LOCAL_LIBS += -L$(T2KGdANA)/lib -ldecayebox
LOCAL_LIBS += -L$(T2KGdANA)/lib -lgd1rmuonselection
LOCAL_LIBS += -L$(T2KGdANA)/lib -lneutrinooscillation
LOCAL_LIBS += -L$(T2KGdANA)/lib -ldistanceviewer
LOCAL_LIBS += -L$(T2KGdANA)/lib -lntaganalysis
LOCAL_LIBS += -L$(T2KGdANA)/lib -ltreemanager
LOCAL_LIBS += -L$(T2KGdANA)/lib -lnninputvariables
#LOCAL_LIBS += -L$(T2KGdANA)/lib -lpthetachecker
LOCAL_LIBS += -L$(ATMPD_ROOT)/lib -lThreeProb
LOCAL_INC += -I$(ANAT2KSK_ROOT)/include
CXXFLAGS += -std=c++11

analysis1Rmu.exe: analysis1Rmu.o
	$(RM) .$@
	LD_RUN_PATH=$(LIBDIR):$(SKOFL_LIBDIR) $(CXX) -g $(CXXFLAGS) -o $@ $^ $(LDLIBS)

analysis1Re.exe: analysis1Re.o
	$(RM) .$@
	LD_RUN_PATH=$(LIBDIR):$(SKOFL_LIBDIR) $(CXX) -g $(CXXFLAGS) -o $@ $^ $(LDLIBS)

protoanalysis.exe: protoanalysis.o
	$(RM) .$@
	LD_RUN_PATH=$(LIBDIR):$(SKOFL_LIBDIR) $(CXX) -g $(CXXFLAGS) -o $@ $^ $(LDLIBS)

MeanMultiplicity.exe: MeanMultiplicity.o
	$(RM) .$@
	LD_RUN_PATH=$(LIBDIR):$(SKOFL_LIBDIR) $(CXX) -g $(CXXFLAGS) -o $@ $^ $(LDLIBS)

createOAinputs.exe: createOAinputs.o
	$(RM) .$@
	LD_RUN_PATH=$(LIBDIR):$(SKOFL_LIBDIR) $(CXX) -g $(CXXFLAGS) -o $@ $^ $(LDLIBS)

PreScan.exe: PreScan.o
	$(RM) .$@
	LD_RUN_PATH=$(LIBDIR):$(SKOFL_LIBDIR) $(CXX) -g $(CXXFLAGS) -o $@ $^ $(LDLIBS)

event.exe: event.o
	$(RM) .$@
	LD_RUN_PATH=$(LIBDIR):$(SKOFL_LIBDIR) $(CXX) -g $(CXXFLAGS) -o $@ $^ $(LDLIBS)

#NoSelection.exe: NoSelection.o
#	$(RM) .$@
#	LD_RUN_PATH=$(LIBDIR):$(SKOFL_LIBDIR) $(CXX) -g $(CXXFLAGS) -o $@ $^ $(LDLIBS)

getNNvariables.exe: getNNvariables.o
	$(RM) .$@
	LD_RUN_PATH=$(LIBDIR):$(SKOFL_LIBDIR) $(CXX) -g $(CXXFLAGS) -o $@ $^ $(LDLIBS)

DecayeTag.exe: DecayeTag.o
	$(RM) .$@
	LD_RUN_PATH=$(LIBDIR):$(SKOFL_LIBDIR) $(CXX) -g $(CXXFLAGS) -o $@ $^ $(LDLIBS)

getPTheta.exe: getPTheta.o
	$(RM) .$@
	LD_RUN_PATH=$(LIBDIR):$(SKOFL_LIBDIR) $(CXX) -g $(CXXFLAGS) -o $@ $^ $(LDLIBS)

VertexSelection.exe: VertexSelection.o
	$(RM) .$@
	LD_RUN_PATH=$(LIBDIR):$(SKOFL_LIBDIR) $(CXX) -g $(CXXFLAGS) -o $@ $^ $(LDLIBS)

GdScaling.exe: GdScaling.o
	$(RM) .$@
	LD_RUN_PATH=$(LIBDIR):$(SKOFL_LIBDIR) $(CXX) -g $(CXXFLAGS) -o $@ $^ $(LDLIBS)

cleananalysis1Rmu:
	$(RM) analysis1Rmu.o analysis1Rmu.exe

cleananalysis1Re:
	$(RM) analysis1Re.o analysis1Re.exe

cleanevent:
	$(RM) evevnt.o event.exe

cleanNoSelection:
	$(RM) NoSelection.o NoSelection.exe

cleanprotoanalysis:
	$(RM) protoanalysis.o protoanalysis.exe

cleancreateOAinputs:
	$(RM) createOAinputs.o createOAinputs.exe

cleangetNNvariables:
	$(RM) getNNvariables.o getNNvariables.exe

cleanDecayeTag:
	$(RM) DecayeTag.o DecayeTag.exe

cleangetPTheta:
	$(RM) getPTheta.o getPTheta.exe

cleanVertexSelection:
	$(RM) VertexSelection.o VertexSelection.exe

cleanGdScaling:
	$(RM) GdScaling.o GdScaling.exe

clean:
	$(RM) *.o *.exe