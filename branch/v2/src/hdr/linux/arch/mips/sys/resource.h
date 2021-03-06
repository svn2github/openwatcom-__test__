/*
 * These five resource limit IDs have a MIPS/Linux-specific ordering,
 * the rest comes from the generic header:
 */
#define RLIMIT_NOFILE           5       /* max number of open files */
#define RLIMIT_AS               6       /* address space limit */
#define RLIMIT_RSS              7       /* max resident set size */
#define RLIMIT_NPROC            8       /* max number of processes */
#define RLIMIT_MEMLOCK          9       /* max locked-in-memory address space */

