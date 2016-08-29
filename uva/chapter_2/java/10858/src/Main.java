import java.util.*;

class Main {
    public static void main(String[] args) {
        new Main().run();
    }

    private void run() {
        sieve();
        Scanner scanner = new Scanner(System.in);
        int n;
        while (true) {
            n = scanner.nextInt();
            BitSet b = new BitSet(n);
            if (n == 0) break;
            List<Integer> factors = factorize(n);
            List<Integer> combined = new ArrayList<Integer>();
            combined.add(1);
            int p = 0;
            while (p < combined.size()) {
                Integer v = combined.get(p);
                for (Integer f : factors) {
                    int t = f * v;
                    if (t >= n || n % t != 0) continue;
                    if (!b.get(t)) {
                        combined.add(t);
                        b.set(t);
                    }
                }
                p++;
            }
            Collections.sort(combined);
            collect(combined, 1, n);
            System.out.println(solutions.size());
            while (!solutions.isEmpty()) {
                List<Integer> list = solutions.poll();
                StringBuilder builder = new StringBuilder();
                boolean first = true;
                for (Integer i : list) {
                    if (!first) builder.append(" ");
                    first = false;
                    builder.append(i);
                }
                System.out.println(builder.toString());
            }
        }
    }

    Stack<Integer> stack = new Stack<Integer>();
    Queue<List<Integer>> solutions = new ArrayDeque<List<Integer>>();

    private void collect(List<Integer> combined, int p, int n) {
        if (n == 1) {
            if (stack.size() < 2) return;
            Enumeration<Integer> elements = stack.elements();
            List<Integer> solution = new ArrayList<Integer>();
            while (elements.hasMoreElements()) {
                solution.add(elements.nextElement());
            }
            solutions.add(solution);
            return;
        }
        for (int i = p; i < combined.size(); i++) {
            int t = combined.get(i);
            if (t > n) break;
            if (n % t != 0) continue;
            stack.push(t);
            collect(combined, i, n / t);
            stack.pop();
        }
    }

    private List<Integer> factorize(int n) {
        List<Integer> factors = new ArrayList<Integer>();
        for (int p : primes) {
            if (p * p > n) break;
            if (n % p != 0) continue;
            factors.add(p);
            while (n % p == 0) n /= p;
        }
        if (n != 1) factors.add(n);
        return factors;
    }

    List<Integer> primes = new ArrayList<Integer>();

    private void sieve() {
        BitSet b = new BitSet(1500);
        primes.add(2);
        for (long i = 3; i < b.size(); i += 2) {
            if (b.get((int) i)) continue;
            primes.add((int) i);
            for (long j = i * i; j < b.size(); j += i) b.set((int) j);
        }
    }
}
