//
//  ContentView.swift
//  Pet Plant
//
//  Created by Lyseron Abergel on 09/06/2026.
//

import SwiftUI

struct ContentView: View {
    @State private var waterProgress = 0;
    @State private var plantState = "DRY";
    var body: some View {
        VStack(spacing: 20) {
            Text("Pet Plant")
                .font(.largeTitle)
                .bold()
            
            Text("Orchid")
                .font(.title)

            Text(plantState)
                .font(.headline)
            
        }
        .padding()
    }
}

#Preview {
    ContentView()
}
