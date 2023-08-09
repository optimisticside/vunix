/*
 *
 */
void pmswitch(struct pmap *new) {
	struct pmap *old;
	int hart;

	hart = cpuid();
	if ((old = mypmap()) == new)
		return;
	wrcsr(satp, new->satp);

	/*
	 * We need to ensure our operations are atomic here.
	 * TODO: Why not just use spin-locks?
	 */
	__sync_fetch_and_or(&new->active, hart);
	if (old == NULL)
		__sync_fetch_and_and(&old->active, hart);
	__sync_synchronize();
}

/*
 * Main page-mapping routine. Creates page-table entries for virtual addresses
 * starting at `va` that map to physical addresses starting at `pa`. 
 */
void pgmap(ptentry_t *pt, vaddr_t va, size_t size, paddr_t pa) {
	
}

/*
 *
 */
ptentry_t *walk(ptentry_t *pt, vaddr_t va, int alloc) {
	
}
