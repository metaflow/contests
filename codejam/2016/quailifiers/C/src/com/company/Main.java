package com.company;

import java.math.BigInteger;
import java.util.*;
import java.util.stream.Collectors;

public class Main {

    public static List<Integer> sieve_primes() {
        int max = 10000;
        BitSet bits = new BitSet(max);
        List<Integer> p = new ArrayList<>();
        p.add(2);
        for (int i = 3; i < max; i+=2) {
            if (bits.get(i)) continue;
            p.add(i);
            for (int j = i * i; j < max; j += i) bits.set(j);
        }
        return p;
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        long tcc = in.nextLong();
        System.out.println(String.format("Case %s#:", tcc));
        long n = in.nextLong();
        long j = in.nextLong();
        String s = "1";
        for (int i = 0; i < n - 2; i++) s += '0';
        s += '1';
        BigInteger b = new BigInteger(s, 2);
        List<BigInteger> primes = sieve_primes().stream()
                .map((Integer a) -> BigInteger.valueOf(a))
                .collect(Collectors.toList());
        while (j != 0) {
            List<BigInteger> divisors = new ArrayList<>();
            for (int i = 2; i < 11; i++) {
                BigInteger v = new BigInteger(b.toString(2), i);
                Optional<BigInteger> f = primes.stream().filter((BigInteger d) -> v.mod(d) == BigInteger.ZERO).findFirst();
                if (f.isPresent()) divisors.add(f.get());
            }
            if (divisors.size() == 9) {
                System.out.print(b.toString(2));
                for (BigInteger d : divisors)
                    System.out.print(String.format(" %s", d));
                System.out.println();
                j--;
            }
            b = b.add(BigInteger.valueOf(2));
        }
    }
}
