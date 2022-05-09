CXX=g++ -m64 -std=c++11
CXXFLAGS=-I. -Iobjs/ -O3 -Wall -mavx2
ISPC=ispc
# ISPCFLAGS=-O2 --target=sse4-i32x8 --arch=x86-64
ISPCFLAGS=-O2 --target=avx2-i32x8 --arch=x86-64

APP_NAME=segment_tree_ispc
OBJDIR=objs

default: $(APP_NAME)

.PHONY: dirs clean

dirs:
		/bin/mkdir -p $(OBJDIR)/

clean:
		/bin/rm -rf $(OBJDIR) *~ $(APP_NAME)

OBJS=$(OBJDIR)/main.o $(OBJDIR)/segment_tree.o $(OBJDIR)/segment_tree_ispc.o

$(APP_NAME): dirs $(OBJS)
		$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

$(OBJDIR)/%.o: %.C
		$(CXX) $< $(CXXFLAGS) -c -o $@

$(OBJDIR)/main.o: segment_tree.H benchmark.C

$(OBJDIR)/segment_tree.o: $(OBJDIR)/segment_tree_ispc.H

$(OBJDIR)/%_ispc.H $(OBJDIR)//%_ispc.o: %.ispc
		$(ISPC) $(ISPCFLAGS) $< -o $(OBJDIR)/$*_ispc.o -h $(OBJDIR)/$*_ispc.H

